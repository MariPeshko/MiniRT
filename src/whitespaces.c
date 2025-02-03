#include "../inc/miniRT.h"

/*c = random character
returns true (aka 1) if c is a whitspace, false (aka 0) if not.
needs stdbool.h for boolean useage*/
bool	is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

/*str = random string
pos = pointer to position in String
Function skips any whitespaces starting at *pos*/
void	skip_whitespace(char *str, int *pos)
{
	while (is_whitespace(str[*pos]))
		*pos += 1;
}