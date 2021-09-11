#include "button.h"

static uint8_t counter=0;
static ST_BUTTON_channels_t channels;

void BUTTON_init(ST_BUTTON_config_t* config)
{
	EN_port port = config->port;
	uint8_t pin = config->pin;
	if (port ==A)
	{
		DIO_voidSetPinDirection(pin,PORTA,INPUT);
	}
	else if(port==B)
	{
		DIO_voidSetPinDirection(pin,PORTB,INPUT);
	}
	else if(port==C)
	{
		DIO_voidSetPinDirection(pin,PORTC,INPUT);
	}
	else
	{
		DIO_voidSetPinDirection(pin,PORTD,INPUT);
	}

	channels.button[counter].port = port;
	channels.button[counter].pin = pin;
	counter++;

}
uint8_t BUTTON_read(uint8_t button_number)
{
	button_number -= 1;
	EN_port port = channels.button[button_number].port;
	uint8_t pin = channels.button[button_number].pin;
	return DIO_u8GetPinValue(pin,port);
}


