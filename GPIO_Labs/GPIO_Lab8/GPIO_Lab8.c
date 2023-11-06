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
bit direction;//Variable to select direction of shifting LEDs



//----------------------PROGRAM MEMORY----------------------


/** PRIVATE PROTOTYPES *********************************************/
void Initialize(void);
void Get_Inputs(void);
void Decide(void);
void Do_Outputs(void);
void Timing(void);





/**SUPPORT ROUTINES*************************************************/

/*---------------------------------------------------------
	Subroutine: Delay_5mS
	Parameters: none
	Returns:nothing
	Synopsis:Creates a 5mS delay when called
---------------------------------------------------------*/
void Delay_5mS(void)
{
	//Make sure the T0IF is cleared
	T0IF = 0;
	//preload the TMR0 register
	TMR0 = 100;
	//Sit here and wait for Timer0 to overflow
	while (T0IF == 0);
}


/**INTERRUPT CODE*************************************************/

/*---------------------------------------------------------
-
	Subroutine: Interrupt Service Routine
	Parameters: none
	Returns:nothing
	Synopsis:Execute this code on any interrupt
---------------------------------------------------------*/
void interrupt PB_PressISR(void)
{
	//First, check if the interrupt occurred as a result of an
	//RA2 change interrupt. If so, clear the RABIF flag so
	//that subsequent interrupts can occur
	if(RABIE && RABIF) RABIF = 0;
	//Check the push button connected to RA0 pin. If 0, then a
	//push button press is indicated
	if(RA2 == 0)
	{
		//Delay for 5mS to filter switch bounce
		Delay_5mS();
		//if RA2 is still 0 then change the direction flag
		if (RA2 == 0) direction = 1;
	}
	//Check the push button connected to RA0 pin. If 1, then a
	//push button release is indicated
	if(RA2 == 1)
	{
		//Delay for 5mS to filter switch bounce
		Delay_5mS();
		//if RA2 is still 1 then change the direction flag
		if (RA2 == 1) direction = 0;
	}
	//Otherwise, keep the direction bit the same as it was
	else direction = direction;
	//Read PORTA to latch RA2 value for the next interrupt
	PORTA = PORTA;
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
	Initialize(); //Initialize the relevant registers
	while(1)
	{
		Decide();//Make any decisions
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
	//Set the least significant bit to 1 so that it can be
	//shifted through
	PORTC = 0b00000001;
	//Clear the PORTA register to a known state
	PORTA = 0b00000000;
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
	//Configure PORTA bit RA0 as Digital input
	ANS2 = 0;
	TRISA2 = 1;
	//Enable Weak Pull-ups on RA2
	WPUA2 = 1;
	nRABPU = 0; //Enable PORTA/PORTB Pull-ups
	//Configure Timer0 to overflow every 5mS
	T0CS = 0; //Select FOSC/4 as Timer0 clock source
	T0SE = 0; //Increment TMR0 on rising clock edge
	PSA = 0; //Assign prescaler to Timer0
	//Select a 1:32 prescaler
	PS0 = 0;
	PS1 = 0;
	PS2 = 1;
	//Initialize the direction flag to shift bits from right-to-left
	//(i.e. 0 = Shift PORTC bits from right-to-left
	// 1 = Shift PORTC bits from left-to-right
	direction = 0;
	//Initialize LED_Output to all zeros
	LED_Output = 0b00000000;
	//Configure for RA2 Interrupt-On-Change
	IOCA2 = 1; //Enable RA2 interrupt-on-change
	RABIE = 1; //Enable change interrupts
	RABIF = 0; //Clear the change interrupt flag
	GIE = 1;//Enable interrupt capability on the
	//PIC16F690 ***ALWAYS DONE LAST*****
	//Read PORTA to latch the current RA2 voltage level
	PORTA = PORTA;
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
	if(direction == 0)
	{
		//First check if LED_Output variable has most
		//significant bit set to 1 or if LED_Output variable is
		//all 0's.
		//If so, re initialize the LED_Output variable so that
		//the most significant bit is set to 1 and all other
		//bits are 0
		if((LED_Output == 0b00000001) || (LED_Output ==	0b00000000)) LED_Output = 0b10000000;
		//If neither of these conditions are true, simply shift
		//the LED_Output variable's contents to the Left by 1
		//bit position
		else LED_Output >>=1;
	}
	else
	{
		//First check if LED_Output variable has the least
		//significant bit set
		//to 1 or if LED_Output variable is all 0's.
		//If so, re initialize the LED_Output variable so that
		//the least significant bit is set to 1 and all other
		//bits are 0
		if((LED_Output == 0b10000000) || (LED_Output ==	0b00000000)) LED_Output = 0b00000001;
		//If neither of these conditions are true, simply shift
		//the LED_Output variable's contents to the Right by 1
		//bit position
		else LED_Output <<=1;
	}
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
	unsigned int delay_var = 9997;
	//Keep looping until the delay_var is
	// equal to zero (should take 10mS)
	while(--delay_var);
}

