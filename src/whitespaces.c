#include "../inc/miniRT.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

/*str = random string
pos = pointer to position in String
Function skips any whitespaces starting at *pos*/
void	skip_whitespace(char *str, int *pos)
{
	while (is_whitespace(str[*pos]))
		*pos += 1;
}

/* switches all whitespaces to spaces */
void	whitespace_to_space(char *line)
{
	int	pos;

	pos = 0;
	while (line && line[pos])
	{
		if (is_whitespace(line[pos]))
			line[pos] = ' ';
		pos++;
	}
}
