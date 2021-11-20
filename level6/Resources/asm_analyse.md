# level6 analysis

## main function analysis

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

<+6> allocate 32 bytes on stack for local variables
<+16> allocate 64 bytes on heap malloc(64)
<+21> store result on stack at esp+0x1c
<+32> allocate 4 bytes on heap malloc(4)
<+37> store result on stack at esp+0x18 (heap address allocated with malloc)
<+50> write m function address at allocated 4 bytes in heap
<+52> copy argv pointer in eax register
<+55> increment eax by four bytes (first command line argument)
<+58> get address of the first command line argument string
<+60> save first command line argument string address in edx
<+73> copy command line argument into allocated with first malloc string (64 bytes)
<+84> call address at esp+0x18 offset (4 bytes allocated by first malloc)

## n function analysis

    Dump of assembler code for function n:
    0x08048454 <+0>:	push   ebp
    0x08048455 <+1>:	mov    ebp,esp
    0x08048457 <+3>:	sub    esp,0x18
    0x0804845a <+6>:	mov    DWORD PTR [esp],0x80485b0
    0x08048461 <+13>:	call   0x8048370 <system@plt>
    0x08048466 <+18>:	leave
    0x08048467 <+19>:	ret
    End of assembler dump.

<+13> call system function system("/bin/cat /home/user/level7/.pass")

## m function analysis

    Dump of assembler code for function m:
    0x08048468 <+0>:	push   ebp
    0x08048469 <+1>:	mov    ebp,esp
    0x0804846b <+3>:	sub    esp,0x18
    0x0804846e <+6>:	mov    DWORD PTR [esp],0x80485d1
    0x08048475 <+13>:	call   0x8048360 <puts@plt>
    0x0804847a <+18>:	leave
    0x0804847b <+19>:	ret
    End of assembler dump.

<+13> call puts function puts("Nope")