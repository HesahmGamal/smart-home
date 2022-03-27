/*
 * Timer_main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousef
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "StdTypes.h"
#include "Utils.h"
#include "DIODrv.h"
#include "Timer.h"
//#include wifi
#define LOCKED 0
#define UNLOCKED  1
#define CORRECT    1
#define WRONG     0
#define DEFAULT    2


void toggle_led(void);
uint8 home_status=WRONG ;   //0 is closed, 1 for open
uint8 user_status=WRONG ;   //0 is closed, 1 for open
uint8 user_arr[][]={"Ahmed","foozy","sayed","wael","askar","hesham","mina","omar","mohab","koko"};
uint8 pass_arr[][]={"1111","2222","3333","4444","5555","6666","7777","8888","9999","1010"};
uint8 wrong_counter=0;

//uint8 * ESP_user=0 ;
//uint8 * ESP_pass=0  ;
 uint8 user_check;
 uint8 pass_check;
 uint8 user_check2;
  uint8 pass_check2;
 uint8 * old_user=-1;
 uint8 * old_pass=-1;


int main ()
{
	DIO_vidSetPinDir( A ,  0 ,  1 ); //set the pin0 drection output  (for buzzer)
	DIO_vidSetPinDir( A ,  1 ,  1 ); //set the pin1 drection output  (for check)
	DIO_vidSetPinDir( A ,  2 ,  1 ); //set the pin1 drection output  (for smart home)

	DIO_vidWriteOnPin(A , 0 , 1);  //write one on pin0
	DIO_vidWriteOnPin(A , 1 , 1 );   //write zero on pin1 for check
	DIO_vidWriteOnPin(A , 2 , 0 );   //for smart home
	_delay_ms(1000);

	sei();  //global interrupt
	Timer1_init (); // timer1 intilization


	//intilize wifi






	while(1)
	{
		TOGGLE_BIT(PORTA,1);

        //check the status
	    check_user();

	    //if   user_status= DEFAULT ;
		home_status=LOCKED;

		//default status***********************************
	    if(user_status== DEFAULT)
	    {

			  //close led
			  //close the door


	    }
	    //correct status***********************************
	    else if(user_status== CORRECT)
	    {

	    	  //check the open the gate
	    	  servo_func_open ();
	    	  while (user_status==CORRECT)
	    	  {   //check the led staus then make action
	    		  //ESP_LED_check=;
	    		  //led_check=strcmp(ESP_LED_check,"ledon");

	    		  if(led_check==0)
	    		  { //open led

	    		  }
	    		  else if (led_check!=0)
	    		  { //close led
	    			     //or toggle to test first

	    		  }

	    		  check_user();
	    		  if (user_status== WRONG || user_status== DEFAULT )
	    		  {
	    			  //close led
	    			  //close the door
	    		  }
	    	  }


	    	//

	    }
	    //wrong status***********************************
	    else if(user_status== WRONG)
	    {
	    	//close led
			  //close the door

	    	//and check again till the counter become 3

			user_check2=strcmp(ESP_user,old_user);
			pass_check2=strcmp(ESP_pass,old_pass );

			if ( user_check2!=0 && pass_check2!=0 )
			{
				old_user=ESP_user;
				old_pass=ESP_pass;
				wrong_counter++;

			}


			if (wrong_counter==3)
			{
				//turn off the buzzer  for 3 seconds
			}

	     }






	}


	return 0;
}


void toggle_led(void)
{
	TOGGLE_BIT(PORTA,0);

}

void servo_func_open (void)
{
	SET_servo_angle(300); //180 degree (open the door)
	_delay_ms(2000);


}

void servo_func_close (void)
{
	SET_servo_angle(175); //90 degree (close the door)
	_delay_ms(2000);


}

void check_user(void)
{

	//uint8 * ESP_user=  ;
	//uint8 * ESP_pass=   ;
	//uint8 ESP_userlen=  ;
	//uint8 ESP_passlen=  ;


	//check if they are correct
	for (int i =0;i<10;i++)
	{

	 user_check=strcmp(ESP_user,user_arr[i]);
     pass_check=strcmp(ESP_pass,pass_arr[i] );

		if ( user_check==0 && pass_check==0 )
		{ //check the passward

			user_status=CORRECT  ;
			home_status=UNLOCKED;
			break;
		}
		else
		{
			if ((ESP_pass == '0') && (ESP_user == '0'))
			{
				user_status= DEFAULT ;
				home_status=LOCKED;
			}
			else
			{
				user_status=WRONG  ;
				home_status=LOCKED;
			}

		}

	}


}




}
