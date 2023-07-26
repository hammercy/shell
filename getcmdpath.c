#include "sshell.h"
/**
 * _getcmdpath - get a full path for the directory
 * @cmd: command to be found
 *
 * Return: full path.
 */
char *_getcmdpath(char *cmd, char *path)
{

	char *crntdir[] = { ".", "/bin", NULL};
	char *cmd_n;
	size_t i;
	if (path != NULL)
	{
		cmd_n = readdir_fcmd(path, cmd);
		if (cmd_n != NULL)
			return (cmd_n);
		else
			return (NULL);
	}
        for (i = 0; crntdir[i] != NULL; i++)
	{
		path = crntdir[i];
		cmd_n = readdir_fcmd(path, cmd);
		if (cmd_n != NULL)
			return (cmd_n);
	}
	cmd_n = readpathfcmd(cmd);
	if (cmd_n != NULL)
		return (cmd_n);
	return (NULL);
}
/**
 * readpathfcmd - each dir in path for command specified.
 * @cmd: command to look for.
 *
 * Return: full path command
 */

char * readpathfcmd(char *cmd)
{
	char *envt = "/etc/environment";
	char **arrptr, **arrptrpth;
	char *cmd_n;
	char buff[1024];
	char *dlmtr[] = {"\"", ":"};
	ssize_t rcnt;
	int fd, i = 1, bsize;
	size_t arrptrln, arrptrpthln;

	

	bsize = 1024;
	fd = open(envt, O_RDONLY);
	if (fd == -1)
		return (NULL);
	intlzstr(buff, bsize, '\0');
	rcnt = read(fd, &buff, bsize);
	if (rcnt < 0)
		return (NULL);
	arrptr = _tostrarr(buff, dlmtr[0], &arrptrln);
	_freemem(arrptr[0]);
	arrptrpth = _tostrarr(arrptr[1], dlmtr[1], &arrptrpthln);
	for (i = 0; arrptrpth[i] != NULL; i++)
		printf("getcmd:arrptrpth[%d] = %s\n", (int)i, arrptrpth[i]);
	arrptrpth = sortpath(arrptrpth);
	for (i = 1; arrptrpth[i] != NULL; i++)
	{
		cmd_n = readdir_fcmd(arrptrpth[i], cmd);
		if (cmd_n != NULL)
		{
			close(fd);
			return (cmd_n);
		}
		_freemem(arrptrpth[i]);
	}
	close(fd);
	return (NULL);
}
/**
 * sortpath - sorts directories in icreasing number of forwardslash
 * @path: array of string pointer to directories
 *
 * Return: return the sorted directories.
 */

char **sortpath(char **path)
{
	size_t i, j, k, cntfsh = 0;
	size_t tmpcnt = 0;
	char *temp;

	
	for (j = 0; path[j] != NULL; j++)
	{
		tmpcnt = cntfsh;
		for (i = j; path[i] != NULL; i++)
		{
			cntfsh = 0;
			for (k = 0; path[i][k] != '\0'; k++)
			{
				if (path[i][k] == '/')
					cntfsh++;
			}
			if (tmpcnt > cntfsh)
			{
				temp = path[i];
				path[i] = path[j];
				path[j] = temp;
			}
		}
	}
	return (path);
}
	
