# level5 asm analysis

## main function analysis

    Dump of assembler code for function main:
    0x08048504 <+0>:	push   ebp
    0x08048505 <+1>:	mov    ebp,esp
    0x08048507 <+3>:	and    esp,0xfffffff0
    0x0804850a <+6>:	call   0x80484c2 <n>
    0x0804850f <+11>:	leave
    0x08048510 <+12>:	ret
    End of assembler dump.

<+6> "n" function call

## n function analysis

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

<+3> Allocate memory on stack
<+35> Call fgets from stdin with buffer of size 520 bytes and read limit of 512 bytes
<+49> Vulnerable printf call with buffer passed as format string
<+61> Exit call with value 1

## o function analysis

    Dump of assembler code for function o:
    0x080484a4 <+0>:	push   ebp
    0x080484a5 <+1>:	mov    ebp,esp
    0x080484a7 <+3>:	sub    esp,0x18
    0x080484aa <+6>:	mov    DWORD PTR [esp],0x80485f0
    0x080484b1 <+13>:	call   0x80483b0 <system@plt>
    0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
    0x080484bd <+25>:	call   0x8048390 <_exit@plt>
    End of assembler dump.

<+13> system function call system("/bin/sh")
<+25> exit function call with value 1