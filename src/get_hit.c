#include "../inc/miniRT.h"

/*for a single ray, find closest collision.
return SUCCESS or FAILURE if ther is /isnt a collision*/
int	get_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	init_hit(&rt->calc.got);
	init_hit(&rt->calc.min);

	//check_plane_hit(cf, &rt->calc, ray);
	//check_sphere_hit(cf, &rt->calc, ray);
	check_cys_hit(cf, rt, ray);
	if (ft_strncmp(rt->calc.min.type, NONE, 4) != SUCCESS)
	{
		print_collision(rt->calc);
		return (SUCCESS);
	}
	return (FAILURE);//so no collisions
}

/*claculates color of pixel based on hit*/
void	get_color()
{
	//printf("Here I would figure out the color to put into pixel\n");
	return ;
}

/*sets pixel color to ambient due to no hit*/
void	get_ambient()
{
//	printf("Here I would get ambient color to put into pixel\n");
	return ;
}

/**
 * 1. Compute the Direction Vector.
 * 2. Store the Ray Origin (camera).
 * 3. Initialize the Ray Direction Vector.
 * Note: we’ve already normalized the basis vectors when 
 * setting up the viewport, you don't need to normalize 
 * the ray direction again when calculating each ray.
*/
void	get_ray(t_mini_rt *rt, t_point pixel, t_point camera)
{
	/*calculates a ray*/
	double	triplet[3];
	triplet[0] = pixel.x - camera.x;
	triplet[1] = pixel.y - camera.y;
	triplet[2] = pixel.z - camera.z;
	rt->calc.ray.c = camera;
	init_vec(&rt->calc.ray.v_dir, triplet);
	return ;
}

/*gets the coordinates of a pixel*/
void	get_pixel(t_vp vp, int h, int w, t_point *pixel)
{
	pixel->x = vp.point.x + h * vp.vertical.x + w * vp.horizontal.x;
	pixel->y = vp.point.y + h * vp.vertical.y + w * vp.horizontal.y;
	pixel->z = vp.point.z + h * vp.vertical.z + w * vp.horizontal.z;
}

/*moves through pixels and delegates coloring it.
at the end: displayable picture*/
int	rays_loop(t_mini_rt *rt)
{
	int	h;
	int	w;

	h = 0;
	init_hit(&rt->calc.min);
	while (h < WIN_HEIGHT)//for each row
	{
		w = 0;
		/* if (h % 10 == 0)
			printf("rays loop h = %d\n", h); */
		while (w < WIN_WIDTH)//for each column
		{
			//printf("[%d][%d]\n", h, w);
			//calculate pixel
			get_pixel(rt->cf.viewp, h, w, &rt->calc.pixel);
			//calculate ray (Pixel - camera)
			get_ray(rt, rt->calc.pixel, rt->cf.cam.point);
			//check for hits and fill pixel color
			if (get_hit(&rt->cf, rt, &rt->calc.ray) == SUCCESS)
				get_color();
			else
				get_ambient();
			w++;
		}
		h++;
	}
	return (SUCCESS);
}
