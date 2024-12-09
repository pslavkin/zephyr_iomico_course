iomico zephyr course
====================

blinky sample to show the project setting in mode T2

Installation
************

.. west init -m git@github.com:pslavkin/zephyr_iomico_course.git --mr blinky iomico_workspace
   cd iomico_workspace
   west update
   west build -b nrf9161dk/nrf9161 -s iomico_blinky -d build
   west flash

Overview
********

this blinky sample is based on the merge of two zephyr basic samples: blinky and
button.

Authors
********

* **Pablo Slavkin**
