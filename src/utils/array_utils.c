#include "../inc/miniRT.h"

/*returns the length of the two dimensional character array map*/
int	map_len(char **map)
{
	int	pos;

	pos = 0;
	while (map && map[pos])
		pos++;
	return (pos);
}
