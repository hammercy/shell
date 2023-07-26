#ifndef SSHELL_H
#define SSHELL_H
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

size_t _strlen(char *s);
void exit(int status);
char **readcmd(int argc, char **argv, size_t *ptrarrln);
char *_getfullpath(char *cmd);
char **_tostrarr(char *buff, char *dlmtr, size_t *ptrarrln);
char **incrarrptrmem(char **arrptr, size_t *arrptrln);
int _chkfordlmtr(char chr, char *dlmtr);
int _streq(char *strs, char *strf);
int _lktostr(char *strs, char *strf);
char *_getcmdpath(char *cmd, char *path);
void intlzstr(char *strptr, size_t strln, char ch);
void intlzarrptr(char **arrptr, size_t arrptrln);
char *_cpsasbtoc(char *str_a, char *str_b);
void _freearrmem(char **ptr, size_t ptrln);
char **iszrpath(char *cmd, char *path);
char *readdir_fcmd(char *dirpth, char *cmd);
char *readpathfcmd(char *cmd);
char **sortpath(char **path);
void _freemem(char *ptr);
#endif
