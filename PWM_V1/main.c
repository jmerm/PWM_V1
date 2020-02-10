//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdbool.h>
#include <stdio.h>
#include <math.h>







// To keep track of which way the compare value is moving
#define EPWM_CMP_UP   1
#define EPWM_CMP_DOWN 0






// Function Prototypes
void InitHalls(void);
void InitPWMA(void);
void InitPWMB(void);
void InitPWMC(void);
//void InitPWM(void);
volatile bool enable = true;
volatile float pos_current;
volatile float neg_current;
volatile float adc_voltage;




//ADC STUFF
void Adc_Config(void);
void DutyCycle_Update(Uint16 throttle_in);
Uint16 LoopCount;
Uint16 DUTY;
volatile float DutyPercent;

//---------------------d
void output_generator(void);

//prototype external interrupt
__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);
__interrupt void xint3_isr(void);


//ADC interrupt prototype
__interrupt void adc_isr(void);





void main(void)
{

    InitSysCtrl(); // Enable PLL WatchDog Enable Peripheral Clocks
    DINT;          // clear interrupts and initialize PIE vector tables
    InitPieCtrl(); // init Pie control registers to default state //enables gpios to cause interrupts

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable(); //init pie vector table with pointers to ISR

    EALLOW;
    PieVectTable.XINT1 = &xint1_isr; // assign XINT1 in table to function
    PieVectTable.XINT2 = &xint2_isr;    // Vector for peripherals service routine points to a
    PieVectTable.XINT3 = &xint3_isr;    // temporary ISR. Temp ISR will only perform a return from
    EDIS;                               // interrupt (IRET) operation.

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;// Enables Interrupt so that interrupt will be service by the temp ISR.
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;// Enable PIE Group 1 INT5

    IER |= M_INT1; // Enable CPU INT1

    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;
    IER |= M_INT12;

    EINT; // Enable Global Interrupts
    ERTM; // Enable global realtime interrupt DBGM

    //INIT HALLS
    InitHalls();
    //--------------------

    //INIT INTERRUPTS FOR HALLS
    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 8;  // selecting gpio 8 for interrupt 1
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 9;  // selecting gpio 9 for interrupt 2
    GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 10; // selecting gpio 10 for interrupt 3
    EDIS;

    XIntruptRegs.XINT1CR.bit.POLARITY = 11; // Rising edge and falling edge interrupt!!!!!!!!
    XIntruptRegs.XINT1CR.bit.ENABLE   = 1;  // Enabling XINT1

    XIntruptRegs.XINT2CR.bit.POLARITY = 11;
    XIntruptRegs.XINT2CR.bit.ENABLE   = 1;

    XIntruptRegs.XINT3CR.bit.POLARITY = 11;
    XIntruptRegs.XINT3CR.bit.ENABLE   = 1;
    EINT; //not sure what this is doing found in example code without comment
   //------------------------------------------------------------------


    //ADC init
    EALLOW;
    PieVectTable.ADCINT1 = &adc_isr; //assign adc_isr
    EDIS;

    InitAdc();
    AdcOffsetSelfCal(); //built in function to set adc up for room temp

    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE //not sure check documentation
    IER |= M_INT1;                     // Enable CPU Interrupt 1
    EINT;                              // Enable Global interrupt INTM //not sure
    ERTM; //not sure

    LoopCount = 0; //uncessary irrelevant sp

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode

    //
    // ADCINT1 trips after AdcResults latch
    //
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    AdcRegs.INTSEL1N2.bit.INT1E     = 1;  // Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;  // Disable ADCINT1 Continuous mode

    //
    // setup EOC1 to trigger ADCINT1 to fire
    //
    AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;

    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 4;  // set SOC0 channel select to ADCINA4
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 2;  // set SOC1 channel select to ADCINA2;
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 3;  // set SOC2 channel select to ADCINA3;
    //
   // set SOC0 start trigger on EPWM6B, due to round-robin SOC0 converts
   // first then SOC1
   //
   AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 16;
   AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 16;
   AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 16;
   //
   // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   //
   AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;
   AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;
   AdcRegs.ADCSOC2CTL.bit.ACQPS    = 6;
   //
   // Assumes ePWM1 clock is already enabled in InitSysCtrl();
   //
   EPwm6Regs.ETSEL.bit.SOCBEN  = 1;        // Enable SOC on A group
   EPwm6Regs.ETSEL.bit.SOCBSEL = 4;        // Select SOC from CMPB on upcount
   EPwm6Regs.ETPS.bit.SOCBPRD  = 1;        // Generate pulse on 1st event
   EPwm6Regs.CMPB = 0x0080;   // Set compare A value   //EPwm1Regs.CMPA.half.CMPA //////MAYBE WRONG
   EPwm6Regs.TBPRD             = 0xFFFF;   // Set period for ePWM1
   EPwm6Regs.TBCTL.bit.CTRMODE = 0;        // count up and start

   InitEPwm1Gpio(); //built in function to assign pwm to gpio
   InitEPwm2Gpio();
   InitEPwm3Gpio();
   InitPWMA(); //user function for init pwm with specific attributes
   InitPWMB();
   InitPWMC();
    // adjust duty for output


   EPwm1Regs.CMPA.half.CMPA = 8; //compare value to set duty cycle 80 / 800 = 10% duty cycle
   EPwm1Regs.CMPB = 8; //inverted logic of the CMPA a leg
   EPwm2Regs.CMPA.half.CMPA = 8;
   EPwm2Regs.CMPB = 8;
   EPwm3Regs.CMPA.half.CMPA = 8;
   EPwm3Regs.CMPB = 8;

    for(;;){
        //this keeps the program running because everything thus far is interrupt driven
    }
}

void InitHalls(){
    EALLOW; // Enable write to protected registers

    // Using Mux to set pins to GPIO pins
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // zero means we are setting it to an general purpose gpio
    GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 0;

    // Setting output pins with no pullup
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1; // setting no pull up
    GpioCtrlRegs.GPAPUD.bit.GPIO8  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO9  = 1;

    //setting to synch with sysclk
                            //NEW, USED TO BE UNCOMMENTED
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 0;
    GpioCtrlRegs.GPAQSEL1.bit.GPIO8  = 0; // No reason to do this. Might default to input. From Allen
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9  = 0;

                            // NEW,
    // Was not here previously, we need to set the direction of 8,9,10: to input
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;  // setting the direction of the gpio to input
    GpioCtrlRegs.GPADIR.bit.GPIO9  = 0;  // inputs -- hall sensors
    GpioCtrlRegs.GPADIR.bit.GPIO8  = 0;
    EDIS;
}
void InitPWMA(){
    // Setupt TBCLK
    EPwm1Regs.TBPRD = 800;  //Period = 1600 TBCLK counts halfway through Taraks triangle diagram peak value
    EPwm1Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero


    // Set compare values

    // Setup counter mode
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode is a symmetric triangle
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW; // not sure from example
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module
    // Setup shadowing
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; //setting up to load on next trigger in our case a clock
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; // not sure
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // not sure

    // Set actions this part gives ups complementary signals
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on event A, up count
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on event A, down count

    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;             // Set PWM1B on event B, up count
    EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;           // Clear PWM1B on event B, down count
    //check this shit later

}
void InitPWMB(){
    // Setupt TBCLK
   EPwm2Regs.TBPRD = 800;  //Period = 1600 TBCLK counts
   EPwm2Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero


   // Set compare values

   // Setup counter mode
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
   EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module
   // Setup shadowing
   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on event A, up count
   EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;             // Set PWM1B on event B, up count
   EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;           // Clear PWM1B on event B, down count

}
void InitPWMC(){

    // Setupt TBCLK
   EPwm3Regs.TBPRD = 800;  //Period = 1600 TBCLK counts
   EPwm3Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero


   // Set compare values

   // Setup counter mode
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
   EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module
   // Setup shadowing
   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on event A, up count
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on event A, down count

   EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;             // Set PWM1B on event B, up count
   EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;           // Clear PWM1B on event B, down count
}


__interrupt void xint1_isr(void) // Interrupt Service Routine?
{
    if(enable){

        output_generator();
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // what ever we needed to do we did acknowledge interrupt
}

__interrupt void xint2_isr(void)
{

    if(enable){

        output_generator();
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void xint3_isr(void)
{

    if(enable){

        output_generator();
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;  //NEW: for xint3, you have to clear group 12. was 1 before.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
0x400 is JUST hall C
0x200 is JUST hall B
0x600 is hall B AND hall C
0x100 is JUST hall A
0x500 is hall A AND hall C
0x300 is hall A AND hall B

GPIO0 is Ahi
GPIO1 is Alo
GPIO2 is Bhi
GPIO3 is Blo
GPIO4 is Chi
GPIO5 is Clo


The truth table used is :

+========+========+========+========+=======+========+=======+=========+=======+
| Hall A | Hall B | Hall C | A High | A Low | B high | B low | C high  | C low |
+========+========+========+========+=======+========+=======+=========+=======+
|      0 |      0 |      1 |      1 |     1 |      1 |     0 |       0 |     1 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+
|      0 |      1 |      0 |      1 |     0 |      0 |     1 |       1 |     1 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+
|      0 |      1 |      1 |      1 |     0 |      1 |     1 |       0 |     1 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+
|      1 |      0 |      0 |      0 |     1 |      1 |     1 |       1 |     0 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+
|      1 |      0 |      1 |      0 |     1 |      1 |     0 |       1 |     1 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+
|      1 |      1 |      0 |      1 |     1 |      0 |     1 |       1 |     0 |
+--------+--------+--------+--------+-------+--------+-------+---------+-------+

//------------------------------------THE INVERTED TRUTH TABLE IS USED ---------------------------------------

*/
////////////////////////////////////////////////////////////////////////////////////////////////////
void DutyCycle_Update(Uint16 throttle_in)
{
    if(throttle_in <= 678){
        EPwm1Regs.CMPA.half.CMPA = 8; // if the throttle reads below lowest possible value do to an error we set the duty cycle to 10%
        EPwm1Regs.CMPB = 8;
        EPwm2Regs.CMPA.half.CMPA = 8;
        EPwm2Regs.CMPB = 8;
        EPwm3Regs.CMPA.half.CMPA = 8;
        EPwm3Regs.CMPB = 8;
    }
    else if(throttle_in >= 3500){
        EPwm1Regs.CMPA.half.CMPA = 700; // if we read above max throttle value due to error set the phase shift to 86%
        EPwm1Regs.CMPB = 700;
        EPwm2Regs.CMPA.half.CMPA = 700;
        EPwm2Regs.CMPB = 700;
        EPwm3Regs.CMPA.half.CMPA = 700;
        EPwm3Regs.CMPB = 700;
    }
    else {
        DUTY = (Uint16) round((.2197*throttle_in)+68.958); //this is based on a curve fit between the max and min throttle voltages and their corresponding adc values
        EPwm1Regs.CMPA.half.CMPA = DUTY;
        EPwm1Regs.CMPB = DUTY;
        EPwm2Regs.CMPA.half.CMPA = DUTY;
        EPwm2Regs.CMPB = DUTY;
        EPwm3Regs.CMPA.half.CMPA = DUTY;
        EPwm3Regs.CMPB = DUTY;
    }

}


void output_generator(void){
    unsigned int halls = GpioDataRegs.GPADAT.all;
    halls = halls & 0x700; // Mask bits 8,9,10 to use for case statement.


    switch(halls)
    {
            case 0x400:
//                GPIO0 is Ahi
//                GPIO1 is Alo
//                GPIO2 is Bhi
//                GPIO3 is Blo
//                GPIO4 is Chi
//                GPIO5 is Clo
                //Blo Chi are both set low to send signal to gate driver (Which is active low)
//                GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; //Chi
//                GpioDataRegs.GPACLEAR.bit.GPIO3 = 1; //Blo
//

                EPwm2Regs.AQCSFRC.bit.CSFB = 01; //Setting Blo  // gnd
                EPwm3Regs.AQCSFRC.bit.CSFA = 11; //Setting Chi  //pmw

                EPwm1Regs.AQCSFRC.bit.CSFA = 10; // turning Ahi on //rail all
                EPwm1Regs.AQCSFRC.bit.CSFB = 10; // turning Alo on
                EPwm2Regs.AQCSFRC.bit.CSFA = 10; // turning Bhi on
                EPwm3Regs.AQCSFRC.bit.CSFB = 11; // turning Clo on

                //SETTING THE REST LOW !!!!!! for quincy :^)
//                GpioDataRegs.GPASET.bit.GPIO1 = 1;
//                GpioDataRegs.GPASET.bit.GPIO2 = 1;
//                GpioDataRegs.GPASET.bit.GPIO5 = 1;
//                GpioDataRegs.GPASET.bit.GPIO0 = 1;
            break;




            case 0x200:
                //just b
                //Alo Bhi
//                GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //ALo
//                GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; //Bhi
//                GpioDataRegs.GPASET.bit.GPIO3 = 1;
//                GpioDataRegs.GPASET.bit.GPIO4 = 1;
//                GpioDataRegs.GPASET.bit.GPIO5 = 1;
//                GpioDataRegs.GPASET.bit.GPIO0 = 1;



                EPwm1Regs.AQCSFRC.bit.CSFB = 01; //Setting Alo low //gnd
                EPwm2Regs.AQCSFRC.bit.CSFA = 11; //Setting Bhi low //pwm

                EPwm1Regs.AQCSFRC.bit.CSFA = 10; // turning Ahi on //rail
                EPwm2Regs.AQCSFRC.bit.CSFB = 11; // turning Blo on
                EPwm3Regs.AQCSFRC.bit.CSFA = 10; // turning Chi on
                EPwm3Regs.AQCSFRC.bit.CSFB = 10; // turning Clo on



            break;

            case 0x600:
                //Alo Chi
                //hall b and hall c
//                GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //Alo
//                GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; //Chi
//                GpioDataRegs.GPASET.bit.GPIO0 = 1;
//                GpioDataRegs.GPASET.bit.GPIO2 = 1;
//                GpioDataRegs.GPASET.bit.GPIO3 = 1;
//                GpioDataRegs.GPASET.bit.GPIO5 = 1;
//
//
//

                EPwm1Regs.AQCSFRC.bit.CSFB = 01; //Setting Alo low //gnd
                EPwm3Regs.AQCSFRC.bit.CSFA = 11; //Setting Chi low //pwm

                EPwm1Regs.AQCSFRC.bit.CSFA = 10; // turning Ahi on
                EPwm2Regs.AQCSFRC.bit.CSFB = 10; // turning Blo on
                EPwm2Regs.AQCSFRC.bit.CSFA = 10; // turning Bhi on
                EPwm3Regs.AQCSFRC.bit.CSFB = 11; // turning Clo on

            break;
            case 0x100:
                //Ahi Clo
//                GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
//                GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
//                GpioDataRegs.GPASET.bit.GPIO1 = 1;
//                GpioDataRegs.GPASET.bit.GPIO2 = 1;
//                GpioDataRegs.GPASET.bit.GPIO3 = 1;
//                GpioDataRegs.GPASET.bit.GPIO4 = 1;
//


                EPwm1Regs.AQCSFRC.bit.CSFA = 11; //Setting Ahi low //pwm
                EPwm3Regs.AQCSFRC.bit.CSFB = 01; //Setting CLo low //gnd

                EPwm1Regs.AQCSFRC.bit.CSFB = 11; // turning Alo on
                EPwm2Regs.AQCSFRC.bit.CSFB = 10; // turning Blo on
                EPwm2Regs.AQCSFRC.bit.CSFA = 10; // turning Bhi on
                EPwm3Regs.AQCSFRC.bit.CSFA = 10; // turning Chi on

            break;
            case 0x500:
                //Ahi blo
//                GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
//                GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
//                GpioDataRegs.GPASET.bit.GPIO1 = 1;
//                GpioDataRegs.GPASET.bit.GPIO2 = 1;
//                GpioDataRegs.GPASET.bit.GPIO4 = 1;
//                GpioDataRegs.GPASET.bit.GPIO5 = 1;



                EPwm1Regs.AQCSFRC.bit.CSFA = 11; //Setting Ahi low //pwm
                EPwm2Regs.AQCSFRC.bit.CSFB = 01; //Setting Blo low // gnd

                EPwm1Regs.AQCSFRC.bit.CSFB = 11; // turning Alo on
                EPwm2Regs.AQCSFRC.bit.CSFA = 10; // turning Bhi on
                EPwm3Regs.AQCSFRC.bit.CSFA = 10; // turning Chi on
                EPwm3Regs.AQCSFRC.bit.CSFB = 10; // turning Clo on

            break;
            case 0x300:
                //Bhi Clo
//                GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
//                GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
//                GpioDataRegs.GPASET.bit.GPIO0 = 1;
//                GpioDataRegs.GPASET.bit.GPIO1 = 1;
//                GpioDataRegs.GPASET.bit.GPIO3 = 1;
//                GpioDataRegs.GPASET.bit.GPIO4 = 1;



                EPwm3Regs.AQCSFRC.bit.CSFB = 01; //Setting Clo low //gnd
                EPwm2Regs.AQCSFRC.bit.CSFA = 11; //Setting Bhi low //pwm

                EPwm1Regs.AQCSFRC.bit.CSFA = 10; // turning Ahi on
                EPwm1Regs.AQCSFRC.bit.CSFB = 10; // turning Alo on
                EPwm2Regs.AQCSFRC.bit.CSFB = 11; // turning Blo on
                EPwm3Regs.AQCSFRC.bit.CSFA = 10; // turning Chi on

            break;
    }



}
__interrupt void
adc_isr(void)
{
    pos_current = 0;
    //-----------------------------------------------------Stuff for the current sensor
    adc_voltage = ((AdcResult.ADCRESULT0)*3.3)/4095;
    pos_current = (abs(adc_voltage)*14.286)-21.6;
    if(pos_current >= 10){ // setting current limits need updated
        enable = false;
        EPwm1Regs.AQCSFRC.bit.CSFA = 1; //Setting Ahi low //pwm
        EPwm2Regs.AQCSFRC.bit.CSFB = 1; //Setting Blo low // gnd

        EPwm1Regs.AQCSFRC.bit.CSFB = 1; // turning Alo on
        EPwm2Regs.AQCSFRC.bit.CSFA = 1; // turning Bhi on
        EPwm3Regs.AQCSFRC.bit.CSFA = 1; // turning Chi on
        EPwm3Regs.AQCSFRC.bit.CSFB = 1; // turning Clo on
    }
    //-------------------------------------------



    // Stuff for throttle------------------------------------------
     DutyCycle_Update(AdcResult.ADCRESULT2);


    //*********************************************************888




    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //ack acd interrupt

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    return;
}

//
// End of File
//



//===========================================================================
// No more.
//===========================================================================
