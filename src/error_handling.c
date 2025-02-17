#include "../inc/miniRT.h"

/*
msg: Macro defined Error message
prints Error message given as Argument
*/
int	display_error(char *msg)
{
	printf(RED "\nError\n%s\n" RESET, msg);
	return (FAILURE);
}