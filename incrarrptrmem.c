#include "sshell.h"
/**
 * _incrarrptrmmry - increase the memeory allocated by malloc
 * @arrptr: hold array of pointer to strings
 * @arrptrln: length  of the old  array pointers
 *
 * Return: new array of pointers  to strings.
 */
char **incrarrptrmem(char **arrptr, size_t *arrptrln)
{
	char **arrptr_n;
	size_t arrptrln_o, i;

	printf("incrarrptrmmry: Entered\n");
	arrptrln_o = *arrptrln;
	*arrptrln = (size_t)2 * (*arrptrln);
	arrptr_n = (char **)malloc((*arrptrln + 1) * sizeof(char));
	if (arrptr_n == NULL)
		return (NULL);
	for (i = 0; i < arrptrln_o; i++)
		arrptr_n[i] = arrptr[i];
	for (i = arrptrln_o; i < *arrptrln; i++)
		arrptr_n[i] = NULL;
	arrptr_n[i] = NULL;
	free (arrptr);
	return (arrptr_n);
}

/**
 * _chkfordlmtr - check a given character  for delimiter characters
 * @chr: hold the character to becheked
 * @dlmtr: array of delimeter values
 * 
 * Return: -1 on failure; index of delimiter on success
 */
int _chkfordlmtr(char chr, char *dlmtr)
{
	int i;

	for (i = 0; dlmtr[i] != '\0'; i++)
	{
		if (chr == dlmtr[i])
			return (1);
	}
	return (-1);
				
}
