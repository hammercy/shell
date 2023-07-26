#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * exit - cause normal process terminatin and the value of status returned.
 * @status: status indicator when returned.
 *
 * Return: status
 */
void exit(int status)
{

	_exit(status);
}
