#include "../inc/miniRT.h"

/*determins weither or not a character is a whitespace*/
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	if (c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

/*str = random string
pos = pointer to position in String
Function skips any whitespaces starting at *pos */
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
