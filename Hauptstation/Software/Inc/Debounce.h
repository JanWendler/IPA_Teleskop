//*******************************************************//
//
//	Name		:	Jan Wendler
//	cDate		:	23.01.2018
//	wDate		:	23.01.2018
//	Projekt	: VR_RC_SIMULATION
//	File		: Debounce.h
//	Function: 
//

#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

//*******************************************************//
//
//	User Input: Please enter the number of buttons you would like to debounce
//							and give your buttons a name.
//

#define NUMBER_OF_BUTTONS 1 //Number of buttons

//
//*******************************************************//
//
//	Fixed Input: No changes needed.
//

//Number of times a Button needs to be "on" to be recognised as such
#define BOUNCE 100

typedef enum 
{
	Negative_Logic = 0, 
	Positive_Logic
}ButtonLogic;

typedef enum 
{
	Negative_Flank = 0,
	Positive_Flank,
	Button_Pressed,
	Button_Released
}ButtonState;

typedef enum
{
	NO_SUCCESS = 0,
	SUCCESSFUL,
	ERROR_MESSAGE
}DebounceRetVal;

typedef struct{
	uint16_t new_button_state;
	uint16_t old_button_state;
	uint16_t counter;
	GPIO_TypeDef *Port;
	uint16_t Pin;
	ButtonState state;
	ButtonLogic logic;
	uint16_t current_button_state;
} myButton_Handler;


DebounceRetVal debounce(myButton_Handler *Button);
void ButtonInit(myButton_Handler Button);
void DEBOUNCE_ERROR(void);
//
//*******************************************************//
#endif /*_DEBOUNCE_H_*/
