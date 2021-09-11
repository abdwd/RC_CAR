#include "motor.h"
static ST_MOTOR_channels_t channels;
static uint8_t counter=0;
void MOTOR_init(ST_MOTOR_config_t* config)
{

	TIMER0_voidInit(TIMER0_CTC_MODE , TIMER0_CTC_DISCONNECT , TIMER0_PRESCALAR_64 , 0);
	EN_port port = config->port;
	uint8_t pin1 = config->pin1;
	uint8_t pin2 = config->pin2;
	if (port ==A)
	{
		DIO_voidSetPinDirection(pin1,PORTA,OUTPUT);
		DIO_voidSetPinDirection(pin2,PORTA,OUTPUT);
	}
	else if(port==B)
	{
		DIO_voidSetPinDirection(pin1,PORTB,OUTPUT);
		DIO_voidSetPinDirection(pin2,PORTB,OUTPUT);
	}
	else if(port==C)
	{
		DIO_voidSetPinDirection(pin1,PORTC,OUTPUT);
		DIO_voidSetPinDirection(pin2,PORTC,OUTPUT);
	}
	else
	{
		DIO_voidSetPinDirection(pin1,PORTD,OUTPUT);
		DIO_voidSetPinDirection(pin2,PORTD,OUTPUT);
	}

	channels.motor[counter].port =port;
	channels.motor[counter].pin1 =pin1;
	channels.motor[counter].pin2 =pin2;
	counter++;
}
void MOTOR_cw(uint8_t motor_number,uint8_t duty_cycle)
{
	motor_number -=1;
	EN_port port = channels.motor[motor_number].port;
	uint8_t pin1 = channels.motor[motor_number].pin1;
	uint8_t pin2 = channels.motor[motor_number].pin2;

	if (port ==A)
	{
		DIO_voidSetPinValue(pin1,A,LOW);
		DIO_voidSetPinValue(pin2,A,HIGH);
	}
	else if(port==B)
	{
		DIO_voidSetPinValue(pin1,B,LOW);
		DIO_voidSetPinValue(pin2,B,HIGH);
	}
	else if(port==C)
	{
		DIO_voidSetPinValue(pin1,C,LOW);
		DIO_voidSetPinValue(pin2,C,HIGH);
	}
	else
	{
		DIO_voidSetPinValue(pin1,D,LOW);
		DIO_voidSetPinValue(pin2,D,HIGH);
	}

	TIMER0_voidSoftwarePWM(PWM_PORT , PWM_PIN , duty_cycle);


}
void MOTOR_ccw(uint8_t motor_number,uint8_t duty_cycle)
{
	motor_number -=1;
	EN_port port = channels.motor[motor_number].port;
	uint8_t pin1 = channels.motor[motor_number].pin1;
	uint8_t pin2 = channels.motor[motor_number].pin2;

	if (port ==A)
	{
		DIO_voidSetPinValue(pin1,A,HIGH);
		DIO_voidSetPinValue(pin2,A,LOW);
	}
	else if(port==B)
	{
		DIO_voidSetPinValue(pin1,B,HIGH);
		DIO_voidSetPinValue(pin2,B,LOW);
	}
	else if(port==C)
	{
		DIO_voidSetPinValue(pin1,C,HIGH);
		DIO_voidSetPinValue(pin2,C,LOW);
	}
	else
	{
		DIO_voidSetPinValue(pin1,D,HIGH);
		DIO_voidSetPinValue(pin2,D,LOW);
	}

	TIMER0_voidSoftwarePWM(PWM_PORT , PWM_PIN , duty_cycle);
}
void MOTOR_stop(uint8_t motor_number)
{
	motor_number -=1;
	EN_port port = channels.motor[motor_number].port;
	uint8_t pin1 = channels.motor[motor_number].pin1;
	uint8_t pin2 = channels.motor[motor_number].pin2;

	if (port ==A)
	{
		DIO_voidSetPinValue(pin1,A,LOW);
		DIO_voidSetPinValue(pin2,A,LOW);
	}
	else if(port==B)
	{
		DIO_voidSetPinValue(pin1,B,LOW);
		DIO_voidSetPinValue(pin2,B,LOW);
	}
	else if(port==C)
	{
		DIO_voidSetPinValue(pin1,C,LOW);
		DIO_voidSetPinValue(pin2,C,LOW);
	}
	else
	{
		DIO_voidSetPinValue(pin1,D,LOW);
		DIO_voidSetPinValue(pin2,D,LOW);
	}
}

