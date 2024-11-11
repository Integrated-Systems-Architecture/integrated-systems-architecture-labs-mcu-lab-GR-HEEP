#include <stdio.h>
#include <stdint.h>

#include "gr_heep.h"

int main(void)
{
    static int32_t * cnt = (int32_t *) SIMPLE_CNT_START_ADDRESS;

    *cnt = 42;

    printf("Simple counter value: %d\n", *cnt);

    return 0;

}
