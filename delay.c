#define __PCB__

#if defined(__PCB__)
#include <10f222.h>
#fuses IOSC4,NOWDT,NOPROTECT, NOMCLR
#use delay(clock=4000000)
#define GP0 PIN_B0
#define GP1 PIN_B1
#define GP2 PIN_B2
#define GP3 PIN_B3

#elif defined(__PCM__)
#include <12C671.h>
#fuses INTRC,NOWDT,NOPROTECT, NOMCLR
#use delay(clock=4000000)
#define GP0 PIN_A0
#define GP1 PIN_A1
#define GP2 PIN_A2
#define GP3 PIN_A3
#define GP4 PIN_A4
#define GP5 PIN_A5

#endif


#define PWR_GATE GP0
#define PWR_RESET GP2


void blink_1 (void)
{
   output_low (PWR_GATE);
   output_low (GP1);

   for (int i=0; i<10; i++) {
      output_high (PWR_GATE);
      output_high (GP1);
      delay_ms (500);
      output_low (PWR_GATE);
      output_low (PWR_GATE);
      delay_ms (500);
   }
}

void main() {
#if defined(__PCB__)
   setup_counters (RTCC_INTERNAL,RTCC_DIV_2);
                               // See .h file for other special
                               // options for setup_counters
#else
   setup_counters (RTCC_INTERNAL,RTCC_DIV_2);
#endif

    output_high (PWR_GATE);
    delay_ms(120000);            // initial 60seconds delay for Jetson boot

   while (TRUE) {
      if (input (PWR_RESET)) {
         output_low (PWR_GATE);
         delay_ms (5000);
         output_high (PWR_GATE);
      }
      delay_ms (20);
   }
}

