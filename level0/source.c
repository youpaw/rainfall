#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>
int main(int ac, const char **av)
{
	char *args[2];
	if (atoi(av[1]) != 423)
	{
		fwrite("No !\n", 1, 5, stdout);
		return (0);
	}
	args[0] = strdup("/bin/sh");
	args[1] = NULL;
	uid_t euid = geteuid();
	gid_t egid = getegid();
	setresuid(euid, euid, euid);
	setresgid(egid, egid, egid);
	execv("/bin/sh", args);
	return (0);
}