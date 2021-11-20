# level7 analysis

## main function analysis

    Dump of assembler code for function main:
    0x08048521 <+0>:	push   ebp
    0x08048522 <+1>:	mov    ebp,esp
    0x08048524 <+3>:	and    esp,0xfffffff0
    0x08048527 <+6>:	sub    esp,0x20
    0x0804852a <+9>:	mov    DWORD PTR [esp],0x8
    0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
    0x08048536 <+21>:	mov    DWORD PTR [esp+0x1c],eax
    0x0804853a <+25>:	mov    eax,DWORD PTR [esp+0x1c]
    0x0804853e <+29>:	mov    DWORD PTR [eax],0x1
    0x08048544 <+35>:	mov    DWORD PTR [esp],0x8
    0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
    0x08048550 <+47>:	mov    edx,eax
    0x08048552 <+49>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048556 <+53>:	mov    DWORD PTR [eax+0x4],edx
    0x08048559 <+56>:	mov    DWORD PTR [esp],0x8
    0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
    0x08048565 <+68>:	mov    DWORD PTR [esp+0x18],eax
    0x08048569 <+72>:	mov    eax,DWORD PTR [esp+0x18]
    0x0804856d <+76>:	mov    DWORD PTR [eax],0x2
    0x08048573 <+82>:	mov    DWORD PTR [esp],0x8
    0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
    0x0804857f <+94>:	mov    edx,eax
    0x08048581 <+96>:	mov    eax,DWORD PTR [esp+0x18]
    0x08048585 <+100>:	mov    DWORD PTR [eax+0x4],edx
    0x08048588 <+103>:	mov    eax,DWORD PTR [ebp+0xc]
    0x0804858b <+106>:	add    eax,0x4
    0x0804858e <+109>:	mov    eax,DWORD PTR [eax]
    0x08048590 <+111>:	mov    edx,eax
    0x08048592 <+113>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048596 <+117>:	mov    eax,DWORD PTR [eax+0x4]
    0x08048599 <+120>:	mov    DWORD PTR [esp+0x4],edx
    0x0804859d <+124>:	mov    DWORD PTR [esp],eax
    0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
    0x080485a5 <+132>:	mov    eax,DWORD PTR [ebp+0xc]
    0x080485a8 <+135>:	add    eax,0x8
    0x080485ab <+138>:	mov    eax,DWORD PTR [eax]
    0x080485ad <+140>:	mov    edx,eax
    0x080485af <+142>:	mov    eax,DWORD PTR [esp+0x18]
    0x080485b3 <+146>:	mov    eax,DWORD PTR [eax+0x4]
    0x080485b6 <+149>:	mov    DWORD PTR [esp+0x4],edx
    0x080485ba <+153>:	mov    DWORD PTR [esp],eax
    0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
    0x080485c2 <+161>:	mov    edx,0x80486e9
    0x080485c7 <+166>:	mov    eax,0x80486eb
    0x080485cc <+171>:	mov    DWORD PTR [esp+0x4],edx
    0x080485d0 <+175>:	mov    DWORD PTR [esp],eax
    0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
    0x080485d8 <+183>:	mov    DWORD PTR [esp+0x8],eax
    0x080485dc <+187>:	mov    DWORD PTR [esp+0x4],0x44
    0x080485e4 <+195>:	mov    DWORD PTR [esp],0x8049960
    0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
    0x080485f0 <+207>:	mov    DWORD PTR [esp],0x8048703
    0x080485f7 <+214>:	call   0x8048400 <puts@plt>
    0x080485fc <+219>:	mov    eax,0x0
    0x08048601 <+224>:	leave
    0x08048602 <+225>:	ret
    End of assembler dump.

<+6> allocate 32 bytes on stack for local variables
<+16> allocate 8 bytes on heap
<+21> save allocated address on stack esp+0x1c
<+29> write into the beginning of the first allocated buffer 0x1
<+42> allocate 8 bytes on heap
<+53> save into the end of the first heap buffer address for the second heap buffer
<+63> allocate 8 bytes on heap
<+68> save allocated address on stack esp+0x18
<+76> write into the beginning of the third allocated buffer 0x2
<+89> allocate 8 bytes on heap
<+96> save into the end of the third heap buffer address for the forth heap buffer
<+103> save command line arguments in eax
<+106> iterate to the first command line argument
<+109> save first command line argument string address into eax
<+111> save eax in edx
<+127> copy into the second buffer first command line argument
<+156> copy into the forth buffer second command line argument
<+178> open pass file for level8 for reading (fopen("/home/user/level8/.pass", "r"))
<+202> call fgets with opened file stream, 68 bytes for reading and undefined c global symbol fgets(c, 68, fs)
<+214> call puts("~~")
<+219> zero eax (return zero)

## m function analysis

    (gdb) disass m
    Dump of assembler code for function m:
    0x080484f4 <+0>:	push   ebp
    0x080484f5 <+1>:	mov    ebp,esp
    0x080484f7 <+3>:	sub    esp,0x18
    0x080484fa <+6>:	mov    DWORD PTR [esp],0x0
    0x08048501 <+13>:	call   0x80483d0 <time@plt>
    0x08048506 <+18>:	mov    edx,0x80486e0
    0x0804850b <+23>:	mov    DWORD PTR [esp+0x8],eax
    0x0804850f <+27>:	mov    DWORD PTR [esp+0x4],0x8049960
    0x08048517 <+35>:	mov    DWORD PTR [esp],edx
    0x0804851a <+38>:	call   0x80483b0 <printf@plt>
    0x0804851f <+43>:	leave
    0x08048520 <+44>:	ret
    End of assembler dump.

<+13> get current time
<+38> printf("%s - %d\n", c, t)