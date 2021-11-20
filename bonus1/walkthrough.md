# bonus1 walkthrough

Given setuid binary:

bonus1@RainFall:~$ ./bonus1
Segmentation fault (core dumped)
bonus1@RainFall:~$ ./bonus1 idk
bonus1@RainFall:~$

There is a memcpy() call which is vulnerable to buffer overflow.
The program take two arguments.
The first argument is converted to an integer using atoi() let's call it nb. If we want to access to memcpy() nb must be less than or equal to 9.
The second argument is copied into a buffer located 40 bytes above the location of the atoi() return. Then nb is compared to 0x574f4c46, if thouse are equal the program will call execl().
The problem is that memcpy() will copy only 4 * nb bytes of argv[2]. So 36 is the maximum number of bytes that can be copied into the buffer (9 * 4 = 36).
Instead of a positive nb we can provide to memcpy a negative nb.
The value of nb is stored in a DWORD (32 bits), the minimum value of a 32-bit signed integer is -2147483647.

                                                       32 bits
                                                          |
    int_min     = 0000 0000 0000 0000 0000 0000 0000 0000 | 1000 0000 0000 0000 0000 0000 0000 0001 = -2147483647
    int_min * 4 = 1111 1111 1111 1111 1111 1111 1111 1110 | 0000 0000 0000 0000 0000 0000 0000 0100 = 4

We can see that after 32 bits, the rest is being ignored, we can abuse that.
If we change the first 32 bits of int_min * 4 in order to have 44 (0b101100), we can retrieve normal decimal number.

                                                        32 bits
                                                           |
    random_int   = 1111 1111 1111 1111 1111 1111 1111 1110 | 0000 0000 0000 0000 0000 0000 0010 1100 = 44 (-8589934548)
    random_int/4 = -2147483637

Now we have our first arg: -2147483637 which is less than 9 and will give us 44 when multiplied by 4.
For the second arg, we need to fill the buffer with the first 40 bytes (padding). Then the last 4 bytes will erase the value of nb and replace it with 0x574f4c46.

    bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
    $ whoami
    bonus2
    $ cat /home/user/bonus2/.pass
    579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
