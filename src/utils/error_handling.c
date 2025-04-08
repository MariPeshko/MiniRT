#include "../inc/miniRT.h"

/*
msg: Macro defined Error message
prints Error message given as Argument
*/
int	display_error(char *msg)
{
	printf(RED "Error\n%s" RESET, msg);
	printf("\n");
	return (FAILURE);
}