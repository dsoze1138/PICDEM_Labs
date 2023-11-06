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

unsigned char LED_Output;//Variable used to set/clear PORTC bits



//----------------------PROGRAM MEMORY----------------------


/** PRIVATE PROTOTYPES *********************************************/
void Initialize(void);
void Get_Inputs(void);
void Decide(void);
void Do_Outputs(void);
void Timing(void);





/**SUPPORT ROUTINES*************************************************/

/*---------------------------------------------------------
Subroutine: Delay_1S
Parameters: none
Returns:nothing
Synopsis:Creates a 1S delay when called
---------------------------------------------------------*/
void Delay_1S(void)
{
	//Create an 8-bit variable called counter
	//and initialize it to 0
	unsigned char counter = 0;
	while(counter <= 15)
	{
		//Make sure the T0IF is cleared
		T0IF = 0;
		//Clear the TMR0 register
		TMR0 = 0;
		//Sit here and wait for Timer0 to overflow
		while (T0IF == 0);
		++counter;
	}
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
		Decide(); //Make any decisions
		Do_Outputs(); //Perform any outputs
		Timing();//Sets execution rate of the
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
	//Clear PORTC to a known state
	PORTC = 0b00000001;
	//Configure PORTC's ANALOG/DIGITAL pins as all Digital
	ANS4 = 0;//Associated with RC0
	ANS5 = 0;//Associated with RC1
	ANS6 = 0;//Associated with RC2
	ANS7 = 0;//Associated with RC3
	ANS8 = 0;//Associated with RC6
	ANS9 = 0;//Associated with RC7
	//Configure PORTC pins as all output
	//i.e. 1 = Input, 0 = Output
	TRISC0 = 0;//Associated with RC0
	TRISC1 = 0;//Associated with RC1
	TRISC2 = 0;//Associated with RC2
	TRISC3 = 0;//Associated with RC3
	TRISC4 = 0;//Associated with RC4
	TRISC5 = 0;//Associated with RC5
	TRISC6 = 0;//Associated with RC6
	TRISC7 = 0;//Associated with RC7
	//Configure Timer0 as follows:
	T0CS = 0; //Use the internal instruction clock
	//FOSC/4 as the clock source
	T0SE = 0;//Increment TMR0 on low-to-high
	//FOSC/4 transition
	PSA = 0;//Assign the prescaler to
	//Timer0
	//Configure Timer0 prescaler to increment
	//TMR0 every 256 FOSC/4 clock transitions
	PS0 = 1;
	PS1 = 1;
	PS2 = 1;
	//Initialize LED_Output to all zeros
	LED_Output = 0b00000000;
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
	//First check if LED_Output variable has most significant bit
	//set to 1 or if LED_Output variable is all 0's.
	//If so, re initialize the LED_Output variable so that the
	//least significant bit is set to 1 and all other bits are
	//cleared to 0
	if((LED_Output == 0b10000000) || (LED_Output == 0b00000000))
	LED_Output = 0b00000001;
	//If neither of these conditions are true, simply shift
	//the LED_Output variable's contents to the Left by 1 bit
	//position
	else LED_Output <<=1;
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
	//Assign the manipulated contents of the
	//LED_Output variable to the PORTC register
	PORTC = LED_Output;
}

/*----------------------------------------------------------
	Subroutine: Timing
	Parameters: none
	Returns:	nothing
	Synopsys:	Controls the how fast code in the main() is executed 
----------------------------------------------------------*/
void Timing(void)

{
	Delay_1S(); //Call the 1 second delay
}

