/*
 * Timer.config.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousef
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*for TIMER0
  normal mode 0
  CTC         1
  PWM         2


 */

#define TIMER0_MODE     2

//***********************************************
/*
 * oc0 mode for fast PWM
 * disconnected   0
 * clear on compare set at the top  1
 * set on compare clear at the top  2
 *
 * */
#define OCO_MODE_FAST_PWM     1

//***********************************************
/*
 * oc0 mode for fast PWM
 * disconnected   0
 * clear on compare set at the top  1
 * set on compare clear at the top  2
 *
 * */
#define OCO_MODE_phase_PWM    1
//***********************************************




/*for TIMER1
 *
  normal mode 0
  PWM phase correct 8bit 1



   PWM phase correct TOP(ICR1)  10
   FAST PWM TOP(ICR1)
 */

#define TIMER1_MODE     14

//***********************************************
/*
 * oc1A mode for fast PWM
 * disconnected   0
 * clear on compare set at the top  1
 * set on compare clear at the top  2
 *
 * */
#define OC1A_MODE_FAST_PWM     1

//***********************************************
/*
 * oc1B mode for fast PWM
 * disconnected   0
 * clear on compare set at the top  1
 * set on compare clear at the top  2
 *
 * */
#define OC1B_MODE_FAST_PWM     0

#endif /* TIMER_CONFIG_H_ */
