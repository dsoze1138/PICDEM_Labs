/********************************************************************
 FileName:     	<Application Name Here>.c
 Dependencies:	See INCLUDES section
 Processor:		PIC16F690 Microcontrollers

 Compiler:		HI-TECH C PRO for the PIC10/12/16 MCU Family (Lite)
 Company:		Microchip Technology, Inc.
 Engineer:		<Your Name Here>

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC® Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description


********************************************************************/
#include	<pic.h>


 //----------------------CONFIGURE DEVICE--------------------
 
	__CONFIG(INTIO & WDTDIS & PWRTDIS & MCLRDIS & 
			UNPROTECT & BORDIS & IESODIS & FCMDIS);

//-----------------------DATA MEMORY------------------------

unsigned char reference_time, thermistor_time,LED_Output;



//----------------------PROGRAM MEMORY----------------------


/** PRIVATE PROTOTYPES *********************************************/
void Initialize(void);
void Get_Inputs(void);
void Decide(void);
void Do_Outputs(void);
void Timing(void);





/**SUPPORT ROUTINES*************************************************/




/**INTERRUPT CODE*************************************************/

void interrupt TMR0_ISR(void)
{
	//Check if Timer0 interrupt has occurred

	if(T0IE&&T0IF) 
	{
		//if so, clear the interrupt flag		
		T0IF = 0;
		//Turn off Timer1 (stop counting)
		TMR1ON = 0;
		//Assign the upper 4-bits of the 16-bit
		//result to PORTC to light the LEDs connected
		//RC0,R1,RC2 and RC3
		PORTC = TMR1H>>4;
		TMR0 = 10;
		//Clear the Timer1 register pair
		TMR1L = 0;
		TMR1H = 0;
		//Turn Timer1 back to start counting again
		TMR1ON = 1;
	}
	else PORTC = PORTC;
}
	

/**SOFTWARE CONTROL LOOP CODE*************************************/
/*----------------------------------------------------------
	Subroutine: main
	Parameters: none
	Returns:	nothing
	Synopsys:	Main program function
-----------------------------------------------------------*/
void main(void)
{

	Initialize();
	while(1);	
	
}

/*----------------------------------------------------------
	Subroutine: INITIALIZE
	Parameters: none
	Returns:	nothing
	Synopsys:	Initializes all registers 
				associated with the application by calling
				initialization functions for each peripheral
----------------------------------------------------------*/
void Initialize(void)
{
//Configure RC0,RC1,RC2 and RC3 as digital outputs
	ANSEL = 0b00001111;
	PORTC = 0;
	TRISC0 = 0;
	TRISC1 = 0;
	TRISC2 = 0;
	TRISC3 = 0;
//Initialize PORTA pin connected to C12IN0-
	TRISA1 = 1;
//Make C1OUT pin an output
	TRISA2 = 0;
//Configure the Comparator 1 as follows:
//Turn on comparator 1
	C1ON = 1;	
//Make C1OUT available externally
	C1OE = 1;
//Connect the non-inverting reference to CVREF
	C1R = 1;	
//Connect the inverting reference to C12IN0-
	C1CH0 = 0;
	C1CH1 = 0;
//Configure the CVREF as follows:
//Route CVREF output to Comparator 1 non-inverting reference
	VRCON = 0;	
//Enable the 0.6V fixed reference voltage
	VP6EN = 1;
//Configure Timer1 as follows
//Make T1CKI and input
	TRISA5 = 1;
	T1CON = 0;
//Select T1CKI as Timer1's clock source
	TMR1CS = 1;
//Initialize the 16-bit Timer1 register pair to 0
	TMR1H = 0;
	TMR1L = 0;
//Turn on Timer1
	TMR1ON = 1;
//Set up Timer0 as follows:
//Use FOSC/4 for Timer0 Clock Source
	OPTION_REG = 0;
	T0CS = 0;
//assign the prescaler to TMR0
	PSA = 0;
//set up prescaler for 1:256
	PS0 = 1;
	PS1 = 1;
	PS2 = 1;
//Enable Timer0 Interrupts
	T0IE = 1;
//Clear the Timer0 overflow interrupt flag
	T0IF = 0;
//Preload TMR0 with 10 to keep overflow period
//less than Timer1 overflow period
	TMR0 = 10;
//Enable global interrupts
	GIE = 1;
}
	
/*----------------------------------------------------------
	Subroutine: Get_Inputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Obtains all off-chip inputs
----------------------------------------------------------*/
void Get_Inputs(void)
{
	//ADD GET_INPUTS CODE HERE	
	
}

/*----------------------------------------------------------
	Subroutine: Decide
	Parameters: none
	Returns:	nothing
	Synopsys:	Function that calls all sub-routines for 
				processing the input data
----------------------------------------------------------*/
void Decide(void)
{
	//ADD DECIDE CODE HERE
}

/*----------------------------------------------------------
	Subroutine: Do_Outputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Ouputs to off-chip circuitry based off of
				Decide function
----------------------------------------------------------*/
void Do_Outputs(void)
{
	//ADD DO_OUTPUTS CODE HERE
}

/*----------------------------------------------------------
	Subroutine: Timing
	Parameters: none
	Returns:	nothing
	Synopsys:	Controls the how fast code in the main() is executed 
----------------------------------------------------------*/
void Timing(void)

{
	//ADD TIMING CODE HERE
}

