/*
 * Timer.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousef
 */


#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "DIODrv.h"
#include "Timer.memmap.h"
#include "Timer.config.h"
#include "Timer.h"
#include <util/delay.h>



static void(* global_pointer)(void)=(void*)0;
static void (*global_pointer_CTC)(void)=(void*)0;

 void Timer0_init ()
 {

  #if(TIMER0_MODE==0)
	 /*ovf intit*/
	 /*select mode ..choosing normal mode*/
	 CLEAR_BIT(TCCR0,3);
	 CLEAR_BIT(TCCR0,6);
	 /*select prescaler...8*/
	 CLEAR_BIT(TCCR0,0);
     CLEAR_BIT(TCCR0,2);
     SET_BIT(TCCR0,1);
     /*enable over flow interrupt*/
     SET_BIT(TIMSK,0);
     /*set preload value*/
     TCNT0=192;
     #elif(TIMER0_MODE==1)
     /*ctc intit*/
     /*select mode ..choosing CTC*/
     SET_BIT(TCCR0,3);
     CLEAR_BIT(TCCR0,6);
     /*choose oc0 mode*/
     CLEAR_BIT(TCCR0,5);
     CLEAR_BIT(TCCR0,4);
     /*select prescaler...8*/
     CLEAR_BIT(TCCR0,0);
     CLEAR_BIT(TCCR0,2);
     SET_BIT(TCCR0,1);
     /*enable over flow interrupt*/
     SET_BIT(TIMSK,1);
     /*put the value of OCR0*/
     OCR0=100;

 #elif(TIMER0_MODE==2)
     /*FAST PWM*/
     /*select mode ..choosing FAST PWM*/
     SET_BIT(TCCR0,3);
     SET_BIT(TCCR0,6);

     /*select prescaler...8*/
     CLEAR_BIT(TCCR0,0);
     CLEAR_BIT(TCCR0,2);
     SET_BIT(TCCR0,1);

     /*OCO pin mode*/
       #if (OCO_MODE_FAST_PWM==0)
     //disconnected
        CLEAR_BIT(TCCR0,5);
        CLEAR_BIT(TCCR0,4);
       #elif (OCO_MODE_FAST_PWM==1)
        //clear oc0 at compare match and set at top
        SET_BIT(DDRB,3); //make oc0 output to can use it
        SET_BIT(TCCR0,5);
        CLEAR_BIT(TCCR0,4);
 	   #elif (OCO_MODE_FAST_PWM==2)
        //set oc0 at compare match and clear at top
        SET_BIT(DDRB,3); //make oc0 output to can use it
        SET_BIT(TCCR0,5);
        SET_BIT(TCCR0,4);
       #endif

#elif(TIMER0_MODE==3)
     /*phase correct PWM*/
     /*select mode ..choosing phase correct PWM*/
     SET_BIT(TCCR0,3);
     CLEAR_BIT(TCCR0,6);
     /*select prescaler...8*/
     CLEAR_BIT(TCCR0,0);
     CLEAR_BIT(TCCR0,2);
     SET_BIT(TCCR0,1);

     /*OCO pin mode*/
     #if (OCO_MODE_phase_PWM==0)
     //disconected
      CLEAR_BIT(TCCR0,5);
      CLEAR_BIT(TCCR0,4);

     #elif (OCO_MODE_phase_PWM==1)
      //clear oc0 on compare match when up counting annd set in comp match when down counting
      SET_BIT(DDRB,3); //make oc0 output to can use it
      SET_BIT(TCCR0,5);
      CLEAR_BIT(TCCR0,4);

	  #elif (OCO_MODE_phase_PWM==2)
      //clear oc0 on compare match when up counting annd set in comp match when down counting
      SET_BIT(DDRB,3); //make oc0 output to can use it
      SET_BIT(TCCR0,5);
      SET_BIT(TCCR0,4);
     #endif

      /* initial vlaue to oc0*/
      OCR0=100;

 #endif

 }


 // intilize timer 1
 void Timer1_init ()
 {
      #if(TIMER1_MODE==0)
	 /*normal mode*/
	 CLEAR_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);

     #elif (TIMER1_MODE==1)
	   /*PWM phase correct 8bit*/
	 SET_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);

     #elif (TIMER1_MODE==2)
	 /*PWM phase correct 9bit*/
	 CLEAR_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
 	 #elif (TIMER1_MODE==3)
	 /*PWM phase correct 10bit*/
	 SET_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==4)
	 /*CTC TOP(OCR1A)*/
	 CLEAR_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==5)
	 /*FAST PWM  8bit*/
	 SET_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==6)
	 /*FAST PWM  9bit*/
	 CLEAR_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==7)
	 /*FAST PWM  10bit*/
	 SET_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 CLEAR_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==8)
	 /*PWM phase and frequency correct  top(ICR1)*/
	 CLEAR_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==9)
	 /*PWM phase and frequency correct  top(OCR1A)*/
	 SET_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==10)
	 /*PWM phase correct TOP(ICR1)*/
	 CLEAR_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==11)
	 /*PWM phase correct TOP(OCR1A)*/
	 SET_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 CLEAR_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
    #elif (TIMER1_MODE==12)
	 /*CTC TOP(ICR1)*/
	 CLEAR_BIT(TCCR1A ,0);
	 CLEAR_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==14)
	 /*FAST PWM TOP(ICR1)*/
	 CLEAR_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
	#elif (TIMER1_MODE==15)
	 /*FAST PWM TOP(OCR1A)*/
	 SET_BIT(TCCR1A ,0);
	 SET_BIT(TCCR1A ,1);
	 SET_BIT(TCCR1B ,3);
	 SET_BIT(TCCR1B ,4);
     #endif


	 /*select prescaler...8*/
	 SET_BIT(TCCR1B,0);
	 CLEAR_BIT(TCCR1B,2);
	 SET_BIT(TCCR1B,1);


	 /*OC1A pin mode----------------------------*/
	      #if (OC1A_MODE_FAST_PWM==0)
	      //disconected
	       CLEAR_BIT(TCCR1A,7);
	       CLEAR_BIT(TCCR1A,6);

	      #elif (OC1A_MODE_FAST_PWM==1)
	       //clear oc0 on compare match when up counting and set in comp match when down counting
	       SET_BIT(DDRD,5); //make oc0 output to can use it
	       SET_BIT(TCCR1A,7);
	       CLEAR_BIT(TCCR1A,6);

	 	  #elif (OC1A_MODE_FAST_PWM==2)
	       //set oc0 on compare match when up counting annd clear in comp match when down counting
	       SET_BIT(DDRD,5); //make oc0 output to can use it
	       SET_BIT(TCCR1A,7);
	       SET_BIT(TCCR1A,6);
	      #endif

	     //choose OC1B-------------------------------------
		#if (OC1B_MODE_FAST_PWM==0)
	      //disconected
	       CLEAR_BIT(TCCR1B,5);
	       CLEAR_BIT(TCCR1B,4);

	      #elif (OC1B_MODE_FAST_PWM==1)
	       //clear oc0 on compare match when up counting annd set in comp match when down counting

	       SET_BIT(DDRD,4); //make oc0 output to can use it
	       SET_BIT(TCCR1B,5);
	       CLEAR_BIT(TCCR1B,4);

	 	  #elif (OC1B_MODE_FAST_PWM==2)
	       //clear oc0 on compare match when up counting annd set in comp match when down counting
	       SET_BIT(DDRD,4); //make oc0 output to can use it
	       SET_BIT(TCCR1B,5);
	       SET_BIT(TCCR1B,4);
	      #endif
      /*set the first value of the timer*/
	       TCNT1 = 0;
	 /*put the value of ICR1H and ICR1L*/
      /*you need 20 ms and tick time is 1 micro second
       * so we will write on the ICR1 the value we want */
       ICR1=2499;

       /*set the value of compare*/
       /*we will choose the angle of servo*/
       OCR1A=175;


 }


 void SET_servo_angle(uint16 value)
  {
	 TOGGLE_BIT(PORTA,0);
 	 OCR1A=value;

  }


//set the value of OCR
 void SET_OCR0_Value(uint8 value)
 {
	 OCR0=value;

 }


 //set the value of preload
 void SET_preload_Value(uint8 value)
  {
	 TCNT0=value;
  }


 //set the duty cycle
 void set_duty_cycle_to_fastPWM(uint8 zero_to_100)
  {
      #if(TIMER0_MODE==2)
	  OCR0=(uint8)( (zero_to_100/100.0)*255);
      #elif(TIMER0_MODE==3)
	  OCR0=(uint8)( ((100-zero_to_100)/100.0)*255);
      #endif

  }


 //pass the address of function that we want to be done by OVF interrupt
 void Timer0_call_back_OVF(void(*copy)(void))
 {
	 global_pointer= copy;
 }

//function we want do with ctc interrupt
 void Timer0_call_back_CTC(void(*copy)(void))
 {
	 global_pointer_CTC= copy;
 }




 /*prototype of isr of vector11*/
 //vector of ovf timer0
 void __vector_11(void)
{

	 static uint16 counter=0;
	 counter++;
	 if (counter==3907)
	 {  //update the preload
		 TCNT0=192;
		 counter=0;

		 //take the function
         if ( global_pointer!=(void*)0)
         {
        	 global_pointer();

         }

	 }

 }

//vector of ctc timer0
 void __vector_10(void)
{

 	 static uint16 counter_CTC=0;
 	 counter_CTC++;
 	 if (counter_CTC==10000)
 	 {  //update the preload

 		 counter_CTC=0;

 		 //take the function
          if ( global_pointer_CTC!=(void*)0)
          {
         	 global_pointer_CTC();

          }

 	 }

  }


 //or interrupt of overflow timer1
 void __vector_9 (void)
 {



 }


 //for interrupt of ctcB timer1
 void __vector_8 (void)
  {



  }

 //for interrupt of ctcA timer1
 void __vector_7 (void)
  {



  }
