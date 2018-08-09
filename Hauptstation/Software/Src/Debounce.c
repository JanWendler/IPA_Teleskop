//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.01.2018
//	wDate		:	23.01.2018
//	Projekt	: VR_RC_SIMULATION
//	File		: Debounce.c
//	Function: 
//

#include "stm32f1xx_hal.h"
#include "Debounce.h"

//*******************************************************//
//
// Function	: 
// Param		: 
// RetVal		: 
//

void ButtonInit(myButton_Handler Button)
{
	GPIO_InitTypeDef GPIOInit;
	
	GPIOInit.Pin = Button.Pin;
	GPIOInit.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(Button.Port, &GPIOInit);
	
}

//*******************************************************//
//
// Function	: This function debounces buttons and returns the state of the button
// Param		: myButton_Handler *Button		--> this struct contains all the information needed for the debouncing process.
//
// RetVal		: 2 = an error occured durring the process.
//						1 = your button is debounced and has the state you want
//						0 = your button is not debounced or has not the state you want
//
DebounceRetVal debounce(myButton_Handler *Button)
{	
	Button->old_button_state = Button->new_button_state;
	Button->current_button_state = HAL_GPIO_ReadPin(Button->Port, Button->Pin);
	//*******************************************************//
	//
	// Debouncing of the button
	//
	if(Button->logic == Positive_Logic)
	{
		if((Button->current_button_state) && (Button->counter < BOUNCE))Button->counter++;
		if((Button->current_button_state == 0) && (Button->counter > 0))Button->counter--;
		if(Button->counter >= BOUNCE) Button->new_button_state = 1;
		if(Button->counter <= 0) Button->new_button_state = 0;
	}
	if(Button->logic == Negative_Logic)
	{
		if((Button->current_button_state == 0) && (Button->counter < BOUNCE))Button->counter++;
		if((Button->current_button_state) && (Button->counter > 0))Button->counter--;
		if(Button->counter >= BOUNCE) Button->new_button_state = 1;
		if(Button->counter <= 0) Button->new_button_state = 0;
	}
	//
	//*******************************************************//
	//
	// Declaring the state of the button and returning the result
	//
	if(Button->state == Positive_Flank) 
	{
		if(Button->new_button_state > Button->old_button_state)
		{
			return(SUCCESSFUL);
		}
		return(NO_SUCCESS);
	}
	
	if(Button->state == Negative_Flank)
	{
		if(Button->new_button_state < Button->old_button_state)
		{
			return(SUCCESSFUL);
		}
		return(NO_SUCCESS);
	}
	if(Button->state == Button_Released)
	{
		if(Button->new_button_state == 0)
		{
			return(SUCCESSFUL);
		}
		return(NO_SUCCESS);
	}
	
	if(Button->state == Button_Pressed)
	{
		if(Button->new_button_state == 1)
		{
			return(SUCCESSFUL);
		}
		return(NO_SUCCESS);
	}
	//
	//*******************************************************//
	DEBOUNCE_ERROR();
	return(ERROR_MESSAGE);
}

//
//
//*******************************************************//
//
// Function	: Error Function
// Param		: non
// RetVal		: non
//
void DEBOUNCE_ERROR(void)
{
	while(1);
}
//
//
//*******************************************************//
