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

/*initialized viewport struct*/
void	init_viewport(t_vp *vp)
{
	double triplet[3];

    triplet[0] = 0.0;
    triplet[1] = 0.0;
    triplet[2] = 0.0;

	if (!vp)
		return;

	// Initialize the corner point and c_point to (0, 0, 0)
	init_point(&vp->point, triplet);
	init_point(&vp->vp_center, triplet);

	// Initialize the horizontal and vertical vectors to (0, 0, 0)
	init_vec(&vp->horizontal, triplet);
	init_vec(&vp->vertical, triplet);

	// Set width and height to 0
	vp->width = 0;
	vp->height = 0;
}