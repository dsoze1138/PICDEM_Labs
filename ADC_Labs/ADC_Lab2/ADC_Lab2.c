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

unsigned char LED_Output = 0; 	//assigned to PORTC to light
								//connected LEDs
bit toggle = 0;//Used to generate waveform on RC0
unsigned char TMR0_preload = 0; //Varied by ADRESH to change
								//frequency of
								//waveform on RC0



//----------------------PROGRAM MEMORY----------------------


/** PRIVATE PROTOTYPES *********************************************/
void Initialize(void);
void Get_Inputs(void);
void Decide(void);
void Do_Outputs(void);
void Timing(void);





/**SUPPORT ROUTINES*************************************************/

/*---------------------------------------------------------
	Subroutine: Delay_1mS
	Parameters: none
	Returns:nothing
	Synopsys:Creates a 1mS delay when called
---------------------------------------------------------*/
void Delay_1mS(void)
{
	unsigned int delay_var = 98;
	//Keep looping until the delay_var is
	// equal to zero (should take 1mS)
	while(--delay_var);
}


/**INTERRUPT CODE*************************************************/




/**SOFTWARE CONTROL LOOP CODE*************************************/
/*----------------------------------------------------------
	Subroutine: main
	Parameters: none
	Returns:	nothing
	Synopsys:	Main program function
-----------------------------------------------------------*/
void main(void)
{

	Initialize(); //Initialize the relevant registers
	while(1)
	{
		Get_Inputs();
		Decide();
		Do_Outputs();
		Timing();
	}
	
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
	//Configure Port:
	PORTB = 0;
	//Disable pin output driver (See TRIS register)
	TRISB4 = 1;
	// Configure RB4 as analog pin as analog
	ANS10 = 1;
	//Configure RC0, RC1, RC2 and RC3 as digital output
	PORTC = 0;
	TRISC0 = 0;
	ANS4 = 0;
	//Configure Timer0 as follows:
	//Select the FOSC/4 internal instruction clock
	//as the clock source for TMR0
	T0CS = 0;
	//Increment TMR0 value on low-to-high transition
	//of the FOSC/4
	T0SE = 0;
	//Assign the prescaler to TMR0
	PSA = 1;
	//Configure the prescaler to increment TMR0
	//at a rate of 1:16
	PS0 = 1;
	PS1 = 1;
	PS2 = 0;
	//Configure the ADC module:
	//Select ADC conversion clock Frc
	ADCS0 = 1;
	ADCS1 = 1;
	ADCS2 = 1;
	//Configure voltage reference using VDD
	VCFG = 0;
	//Select ADC input channel Pin 13 (RB4/AN10)
	CHS0 = 0;
	CHS1 = 1;
	CHS2 = 0;
	CHS3 = 1;
	//Select result format left justified
	ADFM = 0;
	//Turn on ADC module
	ADON = 1;
}
	
/*----------------------------------------------------------
	Subroutine: Get_Inputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Obtains all off-chip inputs
----------------------------------------------------------*/
void Get_Inputs(void)
{
	unsigned char counter = 2;
	//Give ADC hold capacitor time to charge
	//This works out to approximately 8uS
	while(--counter > 0);
	//Start conversion by setting the GO/DONE bit.
	nDONE = 1;
	//Wait for ADC conversion to complete
	//Polling the GO/DONE bit
	// 0 = ADC completed
	// 1 = ADC in progress
	while(nDONE == 1);
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
	//Shift the ADRESH result to the left
	//by three bit positions and assign to
	//TMR0_preload
	TMR0_preload = (uint8_t)(ADRESH<<3);
	//XOR the toggle value with 1
	toggle ^= 1;
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
	//Assign the toggle value to RC0 pin
	RC0 = toggle;
}

/*----------------------------------------------------------
	Subroutine: Timing
	Parameters: none
	Returns:	nothing
	Synopsys:	Controls the how fast code in the main() is executed 
----------------------------------------------------------*/
void Timing(void)

{
	//Clear the T0IF
	T0IF = 0;
	
	//Subtract the TMR0_preload value from 255 and
	//then use to preload TMR0
	TMR0 = (uint8_t)(255 - TMR0_preload);
	
	//Sit here and wait for TMR0 to overflow
	while(T0IF == 0);
}

