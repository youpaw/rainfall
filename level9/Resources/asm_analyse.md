# level9 analysis

## main function analysis

    Dump of assembler code for function main:
    0x080485f4 <+0>:	push   ebp
    0x080485f5 <+1>:	mov    ebp,esp
    0x080485f7 <+3>:	push   ebx
    0x080485f8 <+4>:	and    esp,0xfffffff0
    0x080485fb <+7>:	sub    esp,0x20
    0x080485fe <+10>:	cmp    DWORD PTR [ebp+0x8],0x1
    0x08048602 <+14>:	jg     0x8048610 <main+28>
    0x08048604 <+16>:	mov    DWORD PTR [esp],0x1
    0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
    0x08048610 <+28>:	mov    DWORD PTR [esp],0x6c
    0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
    0x0804861c <+40>:	mov    ebx,eax
    0x0804861e <+42>:	mov    DWORD PTR [esp+0x4],0x5
    0x08048626 <+50>:	mov    DWORD PTR [esp],ebx
    0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
    0x0804862e <+58>:	mov    DWORD PTR [esp+0x1c],ebx
    0x08048632 <+62>:	mov    DWORD PTR [esp],0x6c
    0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
    0x0804863e <+74>:	mov    ebx,eax
    0x08048640 <+76>:	mov    DWORD PTR [esp+0x4],0x6
    0x08048648 <+84>:	mov    DWORD PTR [esp],ebx
    0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
    0x08048650 <+92>:	mov    DWORD PTR [esp+0x18],ebx
    0x08048654 <+96>:	mov    eax,DWORD PTR [esp+0x1c]
    0x08048658 <+100>:	mov    DWORD PTR [esp+0x14],eax
    0x0804865c <+104>:	mov    eax,DWORD PTR [esp+0x18]
    0x08048660 <+108>:	mov    DWORD PTR [esp+0x10],eax
    0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc]
    0x08048667 <+115>:	add    eax,0x4
    0x0804866a <+118>:	mov    eax,DWORD PTR [eax]
    0x0804866c <+120>:	mov    DWORD PTR [esp+0x4],eax
    0x08048670 <+124>:	mov    eax,DWORD PTR [esp+0x14]
    0x08048674 <+128>:	mov    DWORD PTR [esp],eax
    0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
    0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
    0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
    0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
    0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]
    0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax
    0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10]
    0x08048690 <+156>:	mov    DWORD PTR [esp],eax
    0x08048693 <+159>:	call   edx
    0x08048695 <+161>:	mov    ebx,DWORD PTR [ebp-0x4]
    0x08048698 <+164>:	leave  
    0x08048699 <+165>:	ret    
    End of assembler dump.

<+7> 32 bytes are allocated to the main function for its local variables

    0x080485fe <+10>:    cmp    DWORD PTR [ebp+0x8],0x1
    0x08048602 <+14>:    jg     0x8048610 <main+28>
    0x08048604 <+16>:    mov    DWORD PTR [esp],0x1
    0x0804860b <+23>:    call   0x80484f0 <_exit@plt>

<+10> - <+14> jump to 0x8048610 main+28 if argc > 1 (main_args)
<+16> - <+23> call to _exit() with value at the address of esp as argument _exit(1)

    0x08048610 <+28>:    mov    DWORD PTR [esp],0x6c
    0x08048617 <+35>:    call   0x8048530 <_Znwj@plt>
    0x0804861c <+40>:    mov    ebx,eax

<+28> - <+40> initialization of a new operator a = new(108)

    0x0804861e <+42>:    mov    DWORD PTR [esp+0x4],0x5
    0x08048626 <+50>:    mov    DWORD PTR [esp],ebx
    0x08048629 <+53>:    call   0x80486f6 <_ZN1NC2Ei>
    0x0804862e <+58>:    mov    DWORD PTR [esp+0x1c],ebx

<+42> second argument for constructor
<+50> first argument, this is our class
<+53> _ZN1NC2Ei => N::N(int) the constructor <+58> Store the value of ebx (the new N object) at esp+0x1c. *28-58 equivalent in cpp N a = new N(5)

    0x08048632 <+62>:    mov    DWORD PTR [esp],0x6c
    0x08048639 <+69>:    call   0x8048530 <_Znwj@plt>
    0x0804863e <+74>:    mov    ebx,eax
    0x08048640 <+76>:    mov    DWORD PTR [esp+0x4],0x6
    0x08048648 <+84>:    mov    DWORD PTR [esp],ebx
    0x0804864b <+87>:    call   0x80486f6 <_ZN1NC2Ei>
    0x08048650 <+92>:    mov    DWORD PTR [esp+0x18],ebx

<+62> - <+92> same as upper, but the value of ebx (the new N object) is store at esp+0x18
*62-92 equivalent in cpp N b = new N(6)

    0x08048654 <+96>:    mov    eax,DWORD PTR [esp+0x1c]
    0x08048658 <+100>:   mov    DWORD PTR [esp+0x14],eax
    0x0804865c <+104>:   mov    eax,DWORD PTR [esp+0x18]
    0x08048660 <+108>:   mov    DWORD PTR [esp+0x10],eax

<+96> - <+100> save the first N object at esp+0x1c in esp+0x14
<+104> - <+108> save the second N object at esp+0x18 in esp+0x10

    0x08048664 <+112>:   mov    eax,DWORD PTR [ebp+0xc]
    0x08048667 <+115>:   add    eax,0x4
    0x0804866a <+118>:   mov    eax,DWORD PTR [eax]
    0x0804866c <+120>:   mov    DWORD PTR [esp+0x4],eax
    0x08048670 <+124>:   mov    eax,DWORD PTR [esp+0x14]
    0x08048674 <+128>:   mov    DWORD PTR [esp],eax
    0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>

<+112> - <+118> store directly the value of argv[1] in eax, so eax is now a pointer
<+120> - <+128> set arguments for _ZN1N13setAnnotationEPc (N::setAnnotation(char*)) <+131> call to _ZN1N13setAnnotationEPc with N object at esp+0x14 as first arg and av[1] as second (a->setAnnotation(av[1]))

    0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10]
    0x08048680 <+140>:   mov    eax,DWORD PTR [eax]
    0x08048682 <+142>:   mov    edx,DWORD PTR [eax]
    0x08048684 <+144>:   mov    eax,DWORD PTR [esp+0x14]
    0x08048688 <+148>:   mov    DWORD PTR [esp+0x4],eax
    0x0804868c <+152>:   mov    eax,DWORD PTR [esp+0x10]
    0x08048690 <+156>:   mov    DWORD PTR [esp],eax
    0x08048693 <+159>:   call   edx
    0x08048695 <+161>:   mov    ebx,DWORD PTR [ebp-0x4]
    0x08048698 <+164>:   leave
    0x08048699 <+165>:   ret

<+136> store the value at esp+0x10 in eax (eax = *b)
<+140> dereferences the result one time (eax = *eax ; eax = b->method).
<+142> dereferences it again and store the result in edx (edx = *b->method())
<+144> - <+156> set arguments for function call
<+159> call edx (*b->method(*b, *a) ou b->method[0](*b, *a))
<+136> - <+159> after setAllocation, in the main, the program calls the + operator function of b on a. It has to dereference b two times (lines <140> and <142>) to get to the first method which is the + operator
<+161> - <+165> store the return function of main in ebx then we quit the main() function.


## _ZN1NC2Ei N::N(int value) analysis

    Dump of assembler code for function _ZN1NC2Ei:
    0x080486f6 <+0>:     push   ebp
    0x080486f7 <+1>:     mov    ebp,esp
    0x080486f9 <+3>:     mov    eax,DWORD PTR [ebp+0x8]       ; eax = N object passed as parameter
    0x080486fc <+6>:     mov    DWORD PTR [eax],0x8048848     ; *(eax) = vtable.N.0
    0x08048702 <+12>:    mov    eax,DWORD PTR [ebp+0x8]       ; eax = N object passed as parameter
    0x08048705 <+15>:    mov    edx,DWORD PTR [ebp+0xc]       ; the second arg (int 5 or 6)
    0x08048708 <+18>:    mov    DWORD PTR [eax+0x68],edx      ; N_object[0x68] = second arg
    0x0804870b <+21>:    pop    ebp
    0x0804870c <+22>:    ret
    End of assembler dump.

## ZN1NplERS N::operator+(N&) analysis

    Dump of assembler code for function _ZN1NplERS_:
    0x0804873a <+0>:     push   ebp
    0x0804873b <+1>:     mov    ebp,esp
    0x0804873d <+3>:     mov    eax,DWORD PTR [ebp+0x8]       ; eax = first N object (a)
    0x08048740 <+6>:     mov    edx,DWORD PTR [eax+0x68]      ; edx = a->value
    0x08048743 <+9>:     mov    eax,DWORD PTR [ebp+0xc]       ; eax = second N object (b)
    0x08048746 <+12>:    mov    eax,DWORD PTR [eax+0x68]      ; eax = b->value
    0x08048749 <+15>:    add    eax,edx                       ; eax = eax + edx (a->value + b->value)
    0x0804874b <+17>:    pop    ebp
    0x0804874c <+18>:    ret
    End of assembler dump.

## ZN1NmiERS N::operator-(N&) analysis

    Dump of assembler code for function _ZN1NmiERS_:
    0x0804874e <+0>:     push   ebp
    0x0804874f <+1>:     mov    ebp,esp
    0x08048751 <+3>:     mov    eax,DWORD PTR [ebp+0x8]       ; eax = first N object (a)
    0x08048754 <+6>:     mov    edx,DWORD PTR [eax+0x68]      ; edx = a->value
    0x08048757 <+9>:     mov    eax,DWORD PTR [ebp+0xc]       ; eax = second N object (b)
    0x0804875a <+12>:    mov    eax,DWORD PTR [eax+0x68]      ; eax = b->value
    0x0804875d <+15>:    mov    ecx,edx                       ; ecx = a->value
    0x0804875f <+17>:    sub    ecx,eax                       ; ecx = ecx - eax (a->value - b->value)
    0x08048761 <+19>:    mov    eax,ecx                       ; eax = ecx
    0x08048763 <+21>:    pop    ebp
    0x08048764 <+22>:    ret
    End of assembler dump.

## _ZN1N13setAnnotationEPc analysis

    Dump of assembler code for function _ZN1N13setAnnotationEPc:
    0x0804870e <+0>:     push   ebp
    0x0804870f <+1>:     mov    ebp,esp
    0x08048711 <+3>:     sub    esp,0x18
    0x08048714 <+6>:     mov    eax,DWORD PTR [ebp+0xc]       ; eax is pointing on arg2[0]
    0x08048717 <+9>:     mov    DWORD PTR [esp],eax
    0x0804871a <+12>:    call   0x8048520 <strlen@plt>        ; eax = strlen(second arg)
    0x0804871f <+17>:    mov    edx,DWORD PTR [ebp+0x8]       ; edx is pointing on arg1[0]
    0x08048722 <+20>:    add    edx,0x4                       ; edx += 4
    0x08048725 <+23>:    mov    DWORD PTR [esp+0x8],eax       ; 
    0x08048729 <+27>:    mov    eax,DWORD PTR [ebp+0xc]
    0x0804872c <+30>:    mov    DWORD PTR [esp+0x4],eax
    0x08048730 <+34>:    mov    DWORD PTR [esp],edx
    0x08048733 <+37>:    call   0x8048510 <memcpy@plt>
    0x08048738 <+42>:    leave
    0x08048739 <+43>:    ret
    End of assembler dump.
