# M300 II Power Reset Delay

## Compiler

* [CCS PIC Compiler](http://www.ccsinfo.com/) is used.


## How it works

* M300 is powered on.
* 3.3V is supplied to PIC10F microcontroller and it starts monitoring `PWR_RESET` pin.
* 12V output for Jetson NX is off at this moment.
* As Jetson NX is not powered on, PWR_RESET will be / must be `L`.
* PIC10 microcontroller sets `PWR_GATE` pin as `H`, then Jetson NX is powered on.
* **IMPORTANT** On Jetson NX, the `PWR_RESET` must be pulled down to `L` and should never be `H` while Jetson NX operating system is booting.
* if power resetting is needed, Jetson NX will set the `PWR_RESET` pin as `H`. Then the Jetson NX power is off, and `PWR_RESET` will also fall to `L`.
* After 5.0 seconds, the PIC10 microcontroller will pull `PWR_RESET` pin to `H` again, and Jetson NX will be booting again.


## How to modify the reset delay time

In the `main()` function, change the 5000ms integer value.

```c
   while (TRUE) {
      if (input (PWR_RESET)) {
         output_low (PWR_GATE);
         delay_ms (5000);         // modify this value to change delay time
         output_high (PWR_GATE);
      }
      delay_ms (20);
   }
```
