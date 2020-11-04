#ifndef __CLOCK_CONFIG_H__
#define __CLOCK_CONFIG_H__

// pich hardware platform at compile time
#if !defined(AUSF_B) && !defined(AUSF_C) && !defined(AUSF_A)
#define AUSF_B
#endif 

#define PWM_MAX 33
//#define PWM_INIT (1)
#define PWM_INIT (32)

#define FULL_COLOR

#endif // __CLOCK_CONFIG_H__
