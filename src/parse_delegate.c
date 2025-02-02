#include "../inc/miniRT.h"

int	parse_delegate(char *line)//+ largest struct
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_specific(line));//+ largest struct
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_specific(line));//+ largest struct
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_specific(line));//+ largest struct
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_specific(line));//+ largest struct
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_specific(line));//+ largest struct
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_specific(line));//+ largest struct
	return (0);
}

//main for testing parse delegate only
int	main(void)
{
	return (0);
}