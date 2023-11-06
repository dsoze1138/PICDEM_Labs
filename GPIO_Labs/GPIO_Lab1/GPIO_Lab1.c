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





//----------------------PROGRAM MEMORY----------------------


/** PRIVATE PROTOTYPES *********************************************/
void Initialize(void);
void Get_Inputs(void);
void Decide(void);
void Do_Outputs(void);
void Timing(void);





/**SUPPORT ROUTINES*************************************************/




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
	while(1) //Code within curly braces will loop forever
	{
		Do_Outputs(); //Perform any outputs
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
	//Clear PORTC to a known state
	PORTC = 0b00000000;
	//Configure PORTC's ANALOG/DIGITAL pins as all Digital
	ANS4 = 0;//Associated with RC0
	ANS5 = 0;//Associated with RC1
	ANS6 = 0;//Associated with RC2
	ANS7 = 0;//Associated with RC3
	ANS8 = 0;//Associated with RC6
	ANS9 = 0;//Associated with RC7
	//Configure PORTC pins as all output
	//i.e. 1 = Input, 0 = Output
	TRISC0 = 0;//Make RC0 (pin 16) output
	TRISC1 = 0;//Make RC1 (pin 15) output
	TRISC2 = 0;//Make RC2 (pin 14) output
	TRISC3 = 0;//Make RC3 (pin 7) output
	TRISC4 = 0;//Make RC4 (pin 6) output
	TRISC5 = 0;//Make RC5 (pin 5) output
	TRISC6 = 0;//Make RC6 (pin 8) output
	TRISC7 = 0;//Make RC7 (pin 9) output
}
	
/*----------------------------------------------------------
	Subroutine: Get_Inputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Obtains all off-chip inputs
----------------------------------------------------------*/
void Get_Inputs(void)
{
	//ADD GET INPUTS CODE HERE
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
	RC0 = 1;//Make RC0 (pin 16) HIGH (approx. Vdd)
	RC1 = 0;//Make RC1 (pin 15) LOW (approx. Vss)
	RC2 = 1;//Make RC2 (pin 14) HIGH (approx. Vdd)
	RC3 = 1;//Make RC3 (pin 7) HIGH (approx. Vdd)
	RC4 = 0;//Make RC4 (pin 6) LOW (approx. Vss)
	RC5 = 1;//Make RC5 (pin 5) HIGH (approx. Vdd)
	RC6 = 0;//Make RC6 (pin 8) LOW (approx. Vss)
	RC7 = 1;//Make RC7 (pin 9) HIGH (approx. Vdd)
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

