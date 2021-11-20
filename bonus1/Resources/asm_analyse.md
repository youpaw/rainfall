# bonus1 analysis

## main function analysis

    Dump of assembler code for function main:
    0x08048424 <+0>:     push   ebp
    0x08048425 <+1>:     mov    ebp,esp
    0x08048427 <+3>:     and    esp,0xfffffff0
    0x0804842a <+6>:     sub    esp,0x40
    0x0804842d <+9>:     mov    eax,DWORD PTR [ebp+0xc]
    0x08048430 <+12>:    add    eax,0x4
    0x08048433 <+15>:    mov    eax,DWORD PTR [eax]
    0x08048435 <+17>:    mov    DWORD PTR [esp],eax
    0x08048438 <+20>:    call   0x8048360 <atoi@plt>
    0x0804843d <+25>:    mov    DWORD PTR [esp+0x3c],eax
    0x08048441 <+29>:    cmp    DWORD PTR [esp+0x3c],0x9
    0x08048446 <+34>:    jle    0x804844f <main+43>
    0x08048448 <+36>:    mov    eax,0x1
    0x0804844d <+41>:    jmp    0x80484a3 <main+127>
    0x0804844f <+43>:    mov    eax,DWORD PTR [esp+0x3c]
    0x08048453 <+47>:    lea    ecx,[eax*4+0x0]
    0x0804845a <+54>:    mov    eax,DWORD PTR [ebp+0xc]
    0x0804845d <+57>:    add    eax,0x8
    0x08048460 <+60>:    mov    eax,DWORD PTR [eax]
    0x08048462 <+62>:    mov    edx,eax
    0x08048464 <+64>:    lea    eax,[esp+0x14]
    0x08048468 <+68>:    mov    DWORD PTR [esp+0x8],ecx
    0x0804846c <+72>:    mov    DWORD PTR [esp+0x4],edx
    0x08048470 <+76>:    mov    DWORD PTR [esp],eax
    0x08048473 <+79>:    call   0x8048320 <memcpy@plt>
    0x08048478 <+84>:    cmp    DWORD PTR [esp+0x3c],0x574f4c46
    0x08048480 <+92>:    jne    0x804849e <main+122>
    0x08048482 <+94>:    mov    DWORD PTR [esp+0x8],0x0
    0x0804848a <+102>:   mov    DWORD PTR [esp+0x4],0x8048580
    0x08048492 <+110>:   mov    DWORD PTR [esp],0x8048583
    0x08048499 <+117>:   call   0x8048350 <execl@plt>
    0x0804849e <+122>:   mov    eax,0x0
    0x080484a3 <+127>:   leave
    0x080484a4 <+128>:   ret
    End of assembler dump.

<+6> allocate 64 bytes on stack
<+9> - <+15> store directly the value of argv[1] in eax, so eax is now a pointer.
<+17> - <+25> call atoi() with argv[1] then store the result at esp+3c.
<+29> - <+41> if atoi() result is less than or equal to 0x9 jump to main+43, otherwise set eax to 1 and jump to main+127 (leave then ret).
<+43> - <+47> multiply atoi() result by 4 and store resulting value in ecx.
<+54> - <+62> store directly the value of argv[2] in edx.
<+64> eax is now pointing at esp+0x14.
<+68> - <+79> call memcpy() with values at addresses esp, esp+4 and esp+8 as arguments (memcpy(str, argv[2], atoi(argv[1]) * 4)).
<+84> - <+92> if atoi() return is not equal to 0x574f4c46, jump to main+122 (return (0)). Otherwise continue.
<+94> - <+117> call execl() with values at addresses esp, esp+4 and esp+8 as arguments (execl("/bin/sh", "sh", 0)).