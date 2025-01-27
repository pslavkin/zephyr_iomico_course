#include <stdio.h>
#include <stdint.h>
#include <zephyr/kernel.h>

int myUtilFunction(int a, int b) {
   printf("%s hello\r\n", __func__);
    return a + b;
}
