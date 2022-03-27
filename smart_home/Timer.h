/*
 * Timer.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousef
 */

#ifndef TIMER_H_
#define TIMER_H_


 void Timer0_init ();
 void Timer1_init ();
 void SET_servo_angle(uint16 value);

 void __vector_11(void) __attribute((signal)); //for interrupt of overflow timer0
 void __vector_10(void) __attribute((signal)); //for interrupt of ctc timer0
 void __vector_9(void)  __attribute ((signal)); //or interrupt of overflow timer1
 void __vector_8(void)  __attribute ((signal));  //for interrupt of ctcB timer1
 void __vector_7(void)  __attribute ((signal));   //for interrupt of ctcA timer1

 void Timer_call_back_OVF(void(*copy)(void));
 void Timer_call_back_CTC(void(*copy)(void));

 void set_duty_cycle (uint8 zero_to_100);
 void SET_OCR0_Value(uint8 value);
 void SET_preload_Value(uint8 value);




#endif /* TIMER_H_ */
