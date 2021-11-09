# level1 asm analysis

## main function analysis

    Dump of assembler code for function main:
    0x08048480 <+0>:	push   ebp
    0x08048481 <+1>:	mov    ebp,esp
    0x08048483 <+3>:	and    esp,0xfffffff0
    0x08048486 <+6>:	sub    esp,0x50
    0x08048489 <+9>:	lea    eax,[esp+0x10]
    0x0804848d <+13>:	mov    DWORD PTR [esp],eax
    0x08048490 <+16>:	call   0x8048340 <gets@plt>
    0x08048495 <+21>:	leave  
    0x08048496 <+22>:	ret    
    End of assembler dump.

Function prelude:

    0x08048480 <+0>:	push   ebp
    0x08048481 <+1>:	mov    ebp,esp
    0x08048483 <+3>:	and    esp,0xfffffff0

Allocate 80 bytes on stack:

    0x08048486 <+6>:	sub    esp,0x50

Provide allocated buffer as gets function argument:

    0x08048489 <+9>:	lea    eax,[esp+0x10]
    0x0804848d <+13>:	mov    DWORD PTR [esp],eax

<+9> Get effective address of allocated buffer (sp+0x10 => buffer of 64 byte size)
<+13> Overwrite top of the stack with buffer address pointer

Call gets function:

    0x08048490 <+16>:	call   0x8048340 <gets@plt>

Clear stack and return to the previous frame:

    0x08048495 <+21>:	leave
    0x08048496 <+22>:	ret