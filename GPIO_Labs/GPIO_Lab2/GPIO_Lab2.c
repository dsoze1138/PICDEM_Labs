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
	while(1)
	{
		Do_Outputs(); //Perform any outputs
		Timing();	//Sets execution rate of the
					//Software Control Loop
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
	//Set all PORTC bits HIGH (to a known state)
	PORTC = 0b11111111;
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
	RC0 ^= 1;//XOR current RC0 value with 1
	RC1 ^= 1;//XOR current RC1 value with 1
	RC2 ^= 1;//XOR current RC2 value with 1
	RC3 ^= 1;//XOR current RC3 value with 1
	RC4 ^= 1;//XOR current RC4 value with 1
	RC5 ^= 1;//XOR current RC5 value with 1
	RC6 ^= 1;//XOR current RC6 value with 1
	RC7 ^= 1;//XOR current RC7 value with 1
}

/*----------------------------------------------------------
	Subroutine: Timing
	Parameters: none
	Returns:	nothing
	Synopsys:	Controls the how fast code in the main() is executed 
----------------------------------------------------------*/
void Timing(void)

{
	//--------DELAY 1second-------------------------
	//Variable used in delay loop
	unsigned int delay_var1 = 45571;
	unsigned char delay_var2 = 3;
	//Nested while loops to implement a 1 second delay
	//Decrement delay_var2, if 0 jump out of loop
	while(--delay_var2)
	{
		//Decrement delay_var1, if 0 jump out of loop
		while(--delay_var1);
	}
}

