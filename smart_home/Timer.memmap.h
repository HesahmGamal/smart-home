/*
 * Timer.memmap.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yousef
 */

#ifndef TIMER_MEMMAP_H_
#define TIMER_MEMMAP_H_





#define TCCR0   (*(volatile uint8*)0x53)
#define TCNT0   (*(volatile uint8*)0x52)
#define OCR0    (*(volatile uint8*)0x5C)
#define TIMSK   (*(volatile uint8*)0x59)
#define TIFR    (*(volatile uint8*)0x58)


// for timer 1
#define TCCR1A   (*(volatile uint8*) 0x4F )
#define TCCR1B   (*(volatile uint8*) 0x4E )

#define TCNT1H   (*(volatile uint8*) 0x4D )
#define TCNT1L   (*(volatile uint8*) 0x4C )

#define OCR1AH   (*(volatile uint8*) 0x4B )
#define OCR1AL   (*(volatile uint8*) 0x4A )

#define OCR1BH   (*(volatile uint8*) 0x49 )
#define OCR1BL   (*(volatile uint8*) 0x48 )

#define ICR1H    (*(volatile uint8*) 0x47 )
#define ICR1L    (*(volatile uint8*) 0x46 )

#define ICR1    (*(volatile uint16*) 0x46 )
#define OCR1B   (*(volatile uint16*) 0x48 )
#define OCR1A   (*(volatile uint16*) 0x4A )
#define TCNT1   (*(volatile uint16*) 0x4C )

#endif /* TIMER_MEMMAP_H_ */
