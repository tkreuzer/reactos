
#ifndef _TSC_H_
#define _TSC_H_

#define NUM_SAMPLES 4
#define MSR_RDTSC 0x10

#ifndef __ASM__

void __cdecl TscCalibrationISR(void);
extern LARGE_INTEGER HalpCpuClockFrequency;
VOID NTAPI HalpInitializeTsc(void);

#endif

#endif /* !_TSC_H_ */
