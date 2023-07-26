#include "sshell.h"
/**
 * _streq - compares two string 
 * @strs: string source 
 * @strf: string to find
 *
 * Return: 1-success -1-failure.
 */
int _streq(char *strs, char *strf)
{
	size_t i = 0;
	int fail = -1;
	int succ = 1;
	size_t strsln, strfln;
	strsln = _strlen(strs);
	strfln = _strlen(strf);
	if(strsln != strfln)
	{
/*		printf("fail:lenth diff\n");*/
		return (fail);
	}
	while (strs[i] == strf[i])
	{
		if (strs[i] == '\0')
			return (succ);
		i++;
	}
	return (fail);
}
