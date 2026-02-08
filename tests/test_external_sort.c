#include "../include/externalsortengine.h"
#include <stdio.h>

int main(void)
{
    external_sort("input.txt", "output.txt", 5);
    printf("External sort completed\n");
    return 0;
}

