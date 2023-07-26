#include "sshell.h"
/**
 * _tostrarr - arrange string buff into arguments
 * @buff: buffer holding the strings of arguments
 *
 * Return: pointer to array of strings.
 */
char **_tostrarr(char *buff, char *dlmtr, size_t *arrpln)
{
	size_t j,  arrptrln;
	char **arrptr;

	j = 0;
	arrptrln = 16;
/*	printf("tostrarr:input=%s\n", buff); */
	arrptr = (char **)malloc((arrptrln + 1) * sizeof(char));
	if (arrptr == NULL)
		return (NULL);
	arrptr[0] = strtok(buff, dlmtr);
	for (j = 1; arrptr[j - 1] != NULL; j++)
	{
		if (j  >=  arrptrln)
		{
			arrptr = incrarrptrmem(arrptr, &arrptrln);
			if (arrptr == NULL)
				return (NULL);
		}
		arrptr[j] = strtok(NULL, dlmtr);
	}
	*arrpln = j;
	arrptr[j] = NULL;
/*	for (ik = 0; arrptr[ik] != NULL; ik++)
	printf("arrptr[%d] = %s\n", (int)ik, arrptr[ik]);*/
	return (arrptr);
}
