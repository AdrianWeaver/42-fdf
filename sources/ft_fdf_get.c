/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 07:52:36 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/02 15:52:24 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_fdf.h"
#include "libftprintf.h"

/* this function tries to make sure that the map is properly displayed inside
 * the limits of the screen with the best possible size the default value for 
 * the spread must be set quite high at first							*/

void	ft_get_proportion(t_fdf_env *env)
{
	while ((sqrt((env->map->y_max * env->map->y_max)
				+ (env->map->x_max[0] * env->map->x_max[0]))
			* env->var->spread) > env->window_w)
		env->var->spread--;
	env->var->spread--;
	if (env->var->spread < 2)
		env->var->spread = 2;
	env->var->start_spread = env->var->spread;
	ft_get_z_max(env);
}

/* this function gets the coords where the point (0,0) will be casted 
 * it does not include the value of z at the coords (0,0) therefore
 * in extreme scenarii it would be possible for the coords (0,0) to be out of 
 * boundaries															*/

void	ft_get_start(t_fdf_env *env, t_fdf_coords *coords)
{
	int		i;
	int		mean_x;
	int		halfx;
	int		half_y;

	i = -1;
	mean_x = 0;
	half_y = (env->map->y_max / 2) + 0.5;
	while (++i < env->map->y_max)
		mean_x += env->map->x_max[i];
	mean_x /= env->map->y_max;
	halfx = (mean_x / 2) + 0.5;
	coords->x1 = env->var->center_x - (halfx * env->var->spread
			* cos(env->var->o + env->var->angle));
	coords->x1 += half_y * env->var->spread
		* cos(env->var->o - env->var->angle);
	coords->y1 = env->var->center_y - (half_y * env->var->spread
			* sin(env->var->o - env->var->angle));
	coords->y1 -= halfx * env->var->spread * sin(env->var->o + env->var->angle);
	env->var->start_x = coords->x1;
	env->var->start_y = coords->y1;
}

/* jumps to the next point to be drawn, i-e: for (i,j) (i, j+1)
 * and for (i,last_column) it will simply return and the draw_map function
 * will call ft_get_new_line instead */

void	ft_get_new_point(t_fdf_env *env, t_fdf_coords *current,
		int i, int j)
{
	if (j == env->map->x_max[i])
		return ;
	current->x1 += env->var->spread * cos(env->var->o + env->var->angle);
	current->y1 += env->var->spread * sin(env->var->o + env->var->angle);
}

/* jump to the next line at first column */

void	ft_get_new_line(t_fdf_env *env, t_fdf_coords *new_line, int i)
{
	if (i > env->map->y_max)
		return ;
	new_line->x1 = env->var->start_x - i * env->var->spread
		* cos(env->var->o - env->var->angle);
	new_line->y1 = env->var->start_y + i * env->var->spread
		* sin(env->var->o - env->var->angle);
}
