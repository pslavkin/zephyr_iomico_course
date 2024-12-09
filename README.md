iomico zephyr course
====================

blinky sample to show the project setting in mode T2

Installation
************

```
   west init -m git@github.com:pslavkin/zephyr_iomico_course.git --mr blinky iomico_workspace
   cd iomico_workspace
   west update
   west build -b nrf9161dk/nrf9161 -s iomico_blinky -d build
   west flash
```

Using the blinky sample
***********************


launch picocom (or other terminal emulator) to see the output of the sample
press the button to see the callback in the terminal and the leds blinky

```
picocom /dev/ttyACM1  -b115200

Type [C-a] [C-h] to see available commands
Terminal ready
*** Booting Zephyr OS build v4.0.0-rc2 ***
Set up button at gpio@842500 pin 8
Press the button
Toggled led0; counter=0
Toggled led1; counter=0
Button pressed at 308907
btn pressed val: 1
Toggled led0; counter=1

```



Overview
********

this blinky sample is based on the merge of two zephyr basic samples: blinky and
button.

Authors
********

* **Pablo Slavkin**
