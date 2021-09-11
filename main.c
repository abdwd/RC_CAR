#include "TIMER0_interface.h"
#include "DIO_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "motor.h"
#include "button.h"

int main()
{
	/* Buttons Init */
	ST_BUTTON_config_t button_left = {PORTD,0};
	ST_BUTTON_config_t button_move = {PORTD,1};
	ST_BUTTON_config_t button_right = {PORTD,2};
	ST_BUTTON_config_t button_gear = {PORTD,3};

	BUTTON_init(&button_left);
	BUTTON_init(&button_move);
	BUTTON_init(&button_right);
	BUTTON_init(&button_gear);

	/*Motor Init*/
	ST_MOTOR_config_t motor1 = {PORTC,0,1};
	ST_MOTOR_config_t motor2 = {PORTA,0,1};

	MOTOR_init(&motor1);
	MOTOR_init(&motor2);


	/* 0: Initial State
	 * 1: Forward with Duty Cycle = 30 %
	 * 2: Forward with Duty Cycle = 60 %
	 * 3: Forward with Duty Cycle = 90 %
	 * 4: Backward with Duty Cycle = 30 %
	 * 6: Stop
	 * */

	uint8_t state = 0;
	uint8_t previous_state =0;
	uint8_t duty_cycle=0;
	uint8_t direction; /* Forward =1 , Backward=0 */
	uint8_t gear_flag=0;
	while(1)
	{
		/*Gear Button*/
		if(BUTTON_read(4))
		{
			gear_flag=1;
			_delay_ms(30);
			if(BUTTON_read(4))
			{
				state =state + 1 ;
				previous_state = state;
				if(state > 4)
				{
					state = 1;

				}
			}
			while(BUTTON_read(4)){}
		}
		/*Move Button*/
		if (gear_flag==1)
		{
			if(BUTTON_read(2))
			{
				_delay_ms(30);
				if(BUTTON_read(2))
				{

					if(direction) /*Forward*/
					{
						MOTOR_cw(1,duty_cycle);
						MOTOR_cw(2,duty_cycle);
					}
					else /*Backward*/
					{
						MOTOR_ccw(1,duty_cycle);
						MOTOR_ccw(2,duty_cycle);
					}

				}
				while(BUTTON_read(2)){}
				previous_state = state;
				state = 6;
			}
		}
		/*Left Button*/
		if(BUTTON_read(1))
		{
			_delay_ms(30);
			if(BUTTON_read(1))
			{
				MOTOR_cw(1,30);
				MOTOR_ccw(2,30);
			}
			while(BUTTON_read(1)){}
			previous_state = state;
			state = 6;
		}
		/*Right Button*/
		if(BUTTON_read(3))
		{
			_delay_ms(30);
			if(BUTTON_read(3))
			{
				MOTOR_cw(2,30);
				MOTOR_ccw(1,30);
			}
			while(BUTTON_read(3)){}
			previous_state = state;
			state = 6;
		}

		if (state==1)
		{
			duty_cycle = 30 ;
			direction =1;

		}
		else if (state==2)
		{
			duty_cycle = 60 ;
			direction =1;

		}
		else if (state ==3)
		{
			duty_cycle = 90 ;
			direction =1;

		}
		else if (state==4)
		{
			duty_cycle = 30;
			direction = 0;

		}
		else if(state==6) /*STOP*/
		{
			MOTOR_stop(1);
			MOTOR_stop(2);
			state = previous_state;
		}


	}
}


