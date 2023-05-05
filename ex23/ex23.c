#include <stdio.h>
#include <string.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
        to[i]=  from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch (count % 8) {
        case 0:
            do {
                // printf("before %c \t %d \t %c \n", *to, n, *from);
                *to++ = *from++;
                case 7:
                *to++ = *from++;
                case 6:
                *to++ = *from++;
                case 5:
                *to++ = *from++;
                case 4:
                *to++ = *from++;
                case 3:
                *to++ = *from++;
                case 2:
                *to++ = *from++;
                case 1:
                *to++ = *from++;
                // printf("after %c \t %d \t %c \n", *to, n, *from);
            } while (--n > 0);
        }
    }
    // printf("\n");
    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch (count % 8) {
        case 0:
again:  *to++ = *from++;
        // printf("%c \t %d \t %c \n", *to, n, *from);
        case 7:
        *to++ = *from++;
        case 6:
        *to++ = *from++;
        case 5:
        *to++ = *from++;
        case 4:
        *to++ = *from++;
        case 3:
        *to++ = *from++;
        case 2:
        *to++ = *from++;
        case 1:
        *to++ = *from++;
        // printf("%c \t %d \t %c \n", *to, n, *from);
        if (--n > 0)
            goto again;
        }
    }
    // printf("\n");
    return count; 
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; i++) {
        if (data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char from[100] = { 'a' };
    char to[100] = { 'c' };
    int rc = 0;
    // printf("%c, %c, %c \n", from[0], from[5], from[100]);
    // printf("%c, %c, %c \n", to[0], to[5], to[100]);

    // set up the from to have some stuff
    memset(from, 'x', 100);
    // printf("%c, %c, %c \n", from[0], from[5], from[100]);
    // set it to a failure mode
    memset(to, 'y', 100);
    // printf("%c, %c, %c \n", to[0], to[5], to[100]);

    check(valid_copy(to, 100, 'y'), "Not initialized right.");

    // use normal copy to
    rc = normal_copy(from, to, 100);
    check(rc == 100, "Normal copy failed: %d", rc);
    check(valid_copy(to, 100, 'x'), "Normal copy failed");

    // reset
    memset(to, 'y', 100);

    // duffs version
    rc = duffs_device(from, to, 100);
    // printf("%d", rc);
    check(rc == 100, "Duff's device failed: %d", rc);
    check(valid_copy(to, 100, 'x'), "Duff's device failed copy.");


    // reset
    memset(to, 'y', 100);

    // zeds version
    rc = zeds_device(from, to, 100);
    check(rc == 100, "Zed's device failed: %d", rc);
    check(valid_copy(to, 100, 'x'), "Zed's device failed copy.");

    return 0;

error:
    return 1;
}
