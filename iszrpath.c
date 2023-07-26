#include "sshell.h"
/**
 * _iszrpath - check if the command contain a pathe and separate it.
 * @cmd: string pointer to the command.
 * 
 * Return: arrof string containing command and path.
 */
char **iszrpath(char *cmd, char *path)
{
	char **cmd_n;
	int cmdln = 0, fsh = 0;
	int i;
	int ln = 3;

	if (cmd == NULL)
		return (NULL);
	cmd_n = (char **)malloc(ln * sizeof(char *));
	if (cmd_n == NULL)
		return (NULL);
	cmdln = _strlen(cmd);
	if (cmdln == 0)
		return (NULL);
	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			fsh = i;
	}
	if (fsh == 0)
	{
		path = NULL;
		cmd_n[0] = cmd;
		cmd_n[1] = NULL;
		cmd_n[2] = NULL;
		return (cmd_n);
	}
	cmd_n[0]= (char *)malloc((cmdln + 1) * sizeof(char));
	if (cmd_n[0] == NULL)
		return (NULL);
	cmd_n[1] = cmd;
	for (i = fsh + 1; cmd[i] != '\0'; i++)
		cmd_n[0][i - (fsh + 1)] = cmd[i];
	cmd_n[0][i - (fsh + 1)] = '\0';
	for (i = fsh; cmd[i] != '\0'; i++)
		cmd_n[1][i] = '\0';
	path = cmd_n[1];
	(void)(path);
	cmd_n[2] = NULL;
	return (cmd_n);
}
