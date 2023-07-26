#include "sshell.h"

/**
 * main - is a unix command line inpterpreter.
 * 
 * Description: Display a prompt and wait for the user to type
 * -a command. A command line always ends with a new line.
 * -The prompt is dsiplay again each time a command executed.
 * -The command line are simple, no semicolons, pipes,redirectio
 * -The command line are made only of one word. No arguments.
 * -If an executable cannot be found, print an error message and
 *  diplay the prompt again.
 * -Handle errors and end of a file condition (Ctrl + D).
 *
 * Return: 1-success
 */
int main(int argc, char **argv)
{
	size_t ptrarrln;
	char *error, **argcmd, buff[1024];
	char *envrn[] = {NULL};
	ssize_t rcnt, wcnt;
	pid_t mpid;
	int status, fd[2];
	int succ = 0, fail = -1;

	if (argc < 1)
		return (fail);
	error = _cpsasbtoc(argv[0], ":No such file or directory");
	mpid = getpid();
	if (pipe(fd) < 0)
	{
		perror("Pipe");
		return (fail);
	}

	while (1)
	{
		argcmd = readcmd(argc, argv, &ptrarrln);
		if (argcmd == NULL)
		{
			write(1, error, _strlen(error));
			continue;
		}
		if (_streq(argcmd[0], "exit") > 0)
			exit(0);
		mpid = fork();
		if (mpid == -1)
		{
			perror("fork");
			return(fail);
		}
		
		else if(mpid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execve(argcmd[0], argcmd, envrn);
			perror(argv[0]);
			exit(1);
		}
		close(fd[1]);
		while ((rcnt = read(fd[0], buff, sizeof(buff))) > 0)
		{
			wcnt = write(1, buff, rcnt);
			if (wcnt < 0)
				return (fail);
		}
		if (rcnt < 0)
			return (fail);
		wait(&status);
		_freearrmem(argcmd, ptrarrln);

	}
	return (succ);
}
/**
 * readcmd - reads command from std input
 * @argc: number of arg passed to main
 * @argv: arg passed to the main.
 *
 * Return: pointer command read .
 */
char **readcmd(int argc, char **argv, size_t *ptrarrln)
{
	char buff[1024];
	char **argcmd, *path, **cmd;
	ssize_t rcnt, wcnt;
	size_t bsize = 1024;
	char *pmt = "$";
	char *dlmtr_c = " \n";

	(void)(argc + argv);
	wcnt = write(1,pmt, 10);
	if (wcnt == -1)
		return (NULL);
	intlzstr(buff, bsize, '\0');
	rcnt = read(0, buff, bsize);
	if (rcnt == -1)
		return (NULL);
	argcmd = _tostrarr(buff, dlmtr_c, ptrarrln);
	if (argcmd == NULL || argcmd[0] == NULL)
		return (NULL);
	path = NULL;
	cmd = iszrpath(argcmd[0], path);
	if (cmd == NULL)
		return (NULL);
	path = cmd[1];
	argcmd[0] = _getcmdpath(cmd[0], path);
	if (argcmd[0] == NULL || _strlen(argcmd[0]) == 0)
		return (NULL);
	_freemem(path);
	
	return (argcmd);
}

/**
 * intlzstr - initalizes the string or arr of chars.
 * @strptr: pointer to the string to be initialized.
 * @strln: size of the array
 * @ch: character to be initalized with
 *
 */

void intlzstr(char *strptr, size_t strln, char ch)
{
	size_t i;
	
	for (i = 0; i < strln; i++)
		strptr[i] = ch;
}
/**
 * intlzarrptr - initialize array of pointers to NULL
 * @arrptr: pointer to array of pointers
 * @arrptrln: length of the array of pointers.
 *
 * Return: initialized array of pointers.
 */
void intlzarrptr( char **arrptr, size_t arrptrln)
{
	size_t i;

	for (i = 0; i < arrptrln; i++)
		arrptr[i] = NULL;
}
/**
 * _freearrmem - free the array of memory used.
 * @ptr: pointer to memory.
 * @ptrln: length of the memory.
 *
 */
void _freearrmem(char **ptr, size_t ptrln)
{
	size_t  i;

	for (i = 0; i < ptrln; i++)
	{
		if (ptr[i] != NULL)
		{
			free(ptr[i]);
			ptr[i] = NULL;
		}
	}
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	
}
/**
 * _freemem - free a char array of memory used
 * @ptr: pointer to char of array
 */
void _freemem(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
/**
 * _lktostr - finds str in another str
 * @strs: soucre string where we look
 * @strf: the string to be found
 *
 * Return: 1-succ -1-fail.
 */

int _lktostr(char *strs, char *strf)
{
	size_t i, j;
	int fail = -1;
	int succ = 1;

	for (i = 0; strs[i] != '\0'; i++)
	{
		if (strs[i] == strf[0])
		{
			while (strf[j] != '\0' && strs[i + j] != strf[j])
				j++;
			if ((size_t)_strlen(strf) == j)
				return (succ);
		}
	}
	return (fail);
}
