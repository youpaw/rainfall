# level0 asm analysis

    Dump of assembler code for function main:
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
    End of assembler dump.

## Function prelude:

    0x08048ec0 <+0>:	push   ebp
    0x08048ec1 <+1>:	mov    ebp,esp
    0x08048ec3 <+3>:	and    esp,0xfffffff0

<+0> Save previous base pointer on stack
<+1> Update base pointer register with current stack address
<+3> Align stack pointer (allocates from 0 to 16 bytes on stack)

## Allocate local variables:

    0x08048ec6 <+6>:	sub    esp,0x20

<+6> Allocates 32 bytes for all local variables inside current function

## Atoi call:

    0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
    0x08048ecc <+12>:	add    eax,0x4
    0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
    0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
    0x08048ed4 <+20>:	call   0x8049710 <atoi>

<+9> Move command line arguments which are 12 bytes above current base pointer (old ebp address, old eip address, env address)
<+12> Increment to the second command line argument address since they are provided in array of pointers and one pointer in 32 bit architecture is size of 4 bytes
<+17> Move eax on top of the stack as the first argument of the atoi
<+20> Call atoi

## Conditional jump:

    0x08048ed9 <+25>:	cmp    eax,0x1a7
    0x08048ede <+30>:	jne    0x8048f58 <main+152>

<+25> compare atoi return value with 423 constant
<+30> jump to main+152 if they are not equal

### Unequal branch:

    0x08048f58 <+152>:	mov    eax,ds:0x80ee170
    0x08048f5d <+157>:	mov    edx,eax
    0x08048f5f <+159>:	mov    eax,0x80c5350
    0x08048f64 <+164>:	mov    DWORD PTR [esp+0xc],edx
    0x08048f68 <+168>:	mov    DWORD PTR [esp+0x8],0x5
    0x08048f70 <+176>:	mov    DWORD PTR [esp+0x4],0x1
    0x08048f78 <+184>:	mov    DWORD PTR [esp],eax
    0x08048f7b <+187>:	call   0x804a230 <fwrite>
    0x08048f80 <+192>:	mov    eax,0x0

<+152> normal stdout address
<+159> "No!\n" string
<+187> fwrite call
<+192> clear return value

### Equal branch:

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

Set effective uid and gid as current process main uid and gid and call execve("/bin/sh", {"/bin/sh", NULL}, NULL)