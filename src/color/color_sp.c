/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:50 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/03 11:30:31 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	sphere_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_spher	*sp;

	sp = rt->cf.sp;
	while (sp)
	{
		if (coca->sp != NULL && sp->id == coca->sp->id)
		{
			sp = sp->next;
			continue ;
		}
		if (get_hit_sphere(rt, sp, &coca->r_shadow) == SUCCESS
			&& rt->calc.t1 > EPSILON)
			return (true);
		sp = sp->next;
	}
	return (false);
}

t_spher	*get_sphere_pointer(t_mini_rt *rt, t_hit *min)
{
	t_spher	*sp;
	int		i;

	sp = rt->cf.sp;
	i = 1;
	while (i < min->id)
	{
		sp = sp->next;
		i ++;
	}
	return (sp);
}

void	get_sphere_diffuse(t_mini_rt *rt, t_color *diffuse)
{
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir,
			&rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_S);
	diffuse->r = rt->coca.sp->col.r * rt->coca.l.bright
		* rt->coca.l.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.sp->col.g * rt->coca.l.bright
		* rt->coca.l.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.sp->col.b * rt->coca.l.bright
		* rt->coca.l.col.b * d_max(0, rt->coca.tmp);
}

void	get_colors_sphere(t_mini_rt *rt, t_color *ambient, t_color *diffuse)
{
	rt->coca.sp = get_sphere_pointer(rt, &rt->calc.min);
	if (point_minus_point(&rt->calc.min.point, &rt->coca.sp->point,
			&rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_S);
	if (normalize_vector(&rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_S);
	if (point_plus_vector(&rt->calc.min.point, &rt->coca.hit_n, EPSILON,
			&rt->calc.min.point) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_S);
	rt->coca.a = rt->cf.amb;
	rt->coca.l = rt->cf.light;
	ambient->r = rt->coca.sp->col.r * rt->coca.a.col.r
		* rt->coca.a.lighting_ratio;
	ambient->g = rt->coca.sp->col.g * rt->coca.a.col.g
		* rt->coca.a.lighting_ratio;
	ambient->b = rt->coca.sp->col.b * rt->coca.a.col.b
		* rt->coca.a.lighting_ratio;
	if (in_light(rt, &rt->coca) == false)
		return ;
	get_sphere_diffuse(rt, diffuse);
}
