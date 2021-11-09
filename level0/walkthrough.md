# level0 walkthrough
Given 32-bit elf binary:

    file ./level0 
    ./level0: setuid ELF 32-bit LSB executable, Intel 80386, version 1 (GNU/Linux), statically linked, for GNU/Linux 2.6.24, BuildID[sha1]=0x85cf4024dbe79c7ccf4f30e7c601a356ce04f412, not stripped

Lets try to disassemble it with gdb:
    
    gdb ./level0
    (gdb) set dissassembly-flavor intel #view disassembly code in intel syntax
    (gdb) disass *main #disassemble main function
    0x08048ec0 <+0>:	push   ebp
    0x08048ec1 <+1>:	mov    ebp,esp
    0x08048ec3 <+3>:	and    esp,0xfffffff0
    0x08048ec6 <+6>:	sub    esp,0x20
    0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
    0x08048ecc <+12>:	add    eax,0x4
    0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
    0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
    0x08048ed4 <+20>:	call   0x8049710 <atoi>
    0x08048ed9 <+25>:	cmp    eax,0x1a7
    0x08048ede <+30>:	jne    0x8048f58 <main+152>
    0x08048ee0 <+32>:	mov    DWORD PTR [esp],0x80c5348
    0x08048ee7 <+39>:	call   0x8050bf0 <strdup>
    0x08048eec <+44>:	mov    DWORD PTR [esp+0x10],eax
    0x08048ef0 <+48>:	mov    DWORD PTR [esp+0x14],0x0
    0x08048ef8 <+56>:	call   0x8054680 <getegid>
    0x08048efd <+61>:	mov    DWORD PTR [esp+0x1c],eax
    0x08048f01 <+65>:	call   0x8054670 <geteuid>
    0x08048f06 <+70>:	mov    DWORD PTR [esp+0x18],eax
    0x08048f0a <+74>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048f0e <+78>:	mov    DWORD PTR [esp+0x8],eax
    0x08048f12 <+82>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048f16 <+86>:	mov    DWORD PTR [esp+0x4],eax
    0x08048f1a <+90>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048f1e <+94>:	mov    DWORD PTR [esp],eax
    0x08048f21 <+97>:	call   0x8054700 <setresgid>
    0x08048f26 <+102>:	mov    eax,DWORD PTR [esp+0x18]
    0x08048f2a <+106>:	mov    DWORD PTR [esp+0x8],eax
    0x08048f2e <+110>:	mov    eax,DWORD PTR [esp+0x18]
    0x08048f32 <+114>:	mov    DWORD PTR [esp+0x4],eax
    0x08048f36 <+118>:	mov    eax,DWORD PTR [esp+0x18]
    0x08048f3a <+122>:	mov    DWORD PTR [esp],eax
    0x08048f3d <+125>:	call   0x8054690 <setresuid>
    0x08048f42 <+130>:	lea    eax,[esp+0x10]
    0x08048f46 <+134>:	mov    DWORD PTR [esp+0x4],eax
    0x08048f4a <+138>:	mov    DWORD PTR [esp],0x80c5348
    0x08048f51 <+145>:	call   0x8054640 <execv>
    0x08048f56 <+150>:	jmp    0x8048f80 <main+192>
    0x08048f58 <+152>:	mov    eax,ds:0x80ee170
    0x08048f5d <+157>:	mov    edx,eax
    0x08048f5f <+159>:	mov    eax,0x80c5350
    0x08048f64 <+164>:	mov    DWORD PTR [esp+0xc],edx
    0x08048f68 <+168>:	mov    DWORD PTR [esp+0x8],0x5
    0x08048f70 <+176>:	mov    DWORD PTR [esp+0x4],0x1
    0x08048f78 <+184>:	mov    DWORD PTR [esp],eax
    0x08048f7b <+187>:	call   0x804a230 <fwrite>
    0x08048f80 <+192>:	mov    eax,0x0
    0x08048f85 <+197>:	leave  
    0x08048f86 <+198>:	ret

First of all we can see atoi function call at +20 offset inside main:

    0x08048ed4 <+20>:	call   0x8049710 <atoi>

To examine arguments provided to the function call we need to look at what was pushed on top of the stack.
In 32-bit elfs function arguments are provided via stack in revers order (first argument at the top, so it would be pushed last).
Lets set a breakpoint right before atoi call and try to run this program:

    (gdb) b *main+20 #set breakpoint at main+20
    (gdb) run "smth" #provide argument "smth", otherwise binary would segfault
    (gdb) x/1x $sp #print address of the first element from top of the stack
    0xbffff710:	0xbffff8fa
    (gdb) printf "%s\n", 0xbffff8fa #it's an argument which we provided
    smth

Knowing that atoi function takes one argument we need to print only one element from top of the stack.
Since atoi function converts string to integer we can display stack element value using printf.
It turns out to be the first argument which we provided to the program run.
We can see that after atoi call eax register (atoi return value) is compared with constant 0x1a7 (423 in decimal) and if they are not equal then program jumps to main+152 offset.
If we continue program run we would see what happens:

    (gdb) c
    Continuing.
    No !
    [Inferior 1 (process 2735) exited normally

It just prints "No !" and exits with 0 return code.
If we provide "423" argument then program will set effective uid and gid as real an execute dash

    (gdb) run 423
    Starting program: /home/user/level0/level0 423
    process 2741 is executing new program: /bin/dash

Now we can get flag containing in home directory of level1 user:

    ./level0 423
    $ cat /home/user/level1/.pass
    1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a