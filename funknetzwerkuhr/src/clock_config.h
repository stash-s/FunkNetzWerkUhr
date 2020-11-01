#ifndef __CLOCK_CONFIG_H__
#define __CLOCK_CONFIG_H__

// pich hardware platform at compile time
#if !defined(AUSF_B) && !defined(AUSF_C) && !defined(AUSF_A)
#define AUSF_B
#endif 

#ifdef AUSF_A

#elif defined(AUSF_B)
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
const int LATCH_PIN = 15;

#elif defined(AUSF_C)
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
const int LATCH_PIN = 15;
#endif

#define PWM_MAX 33
//#define PWM_INIT (1)
#define PWM_INIT (32)

#define FULL_COLOR

#endif // __CLOCK_CONFIG_H__
