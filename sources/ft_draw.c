/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:10 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/01 18:21:46 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h> 
#include "libftprintf.h"
#include <stdio.h> 

/* secure bresenham called in the followed functions is just a safety to
 * avoid writing out of the boundaries of the image 					*/

//need to create new coords and add z at the last moment
void	ft_draw_horizontal(t_fdf_env *env, t_fdf_coords current_point,
		int i, int j)
{
	t_fdf_coords	next_point;

	if (j > env->map->x_max[i])
		return ;
	next_point.x1 = current_point.x1
		+ (env->var->spread * cos(0.5236 + env->var->angle));
	next_point.y1 = current_point.y1 + (env->var->spread * sin(0.5236
				+ env->var->angle) - (env->map->z[i][j + 1]
				* env->var->mod_height));
	next_point.y1 += (env->map->z[i][j] * env->var->mod_height);
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (j < env->map->x_max[i] - 1)
		ft_secure_bresenham(env, current_point, 0xffffff, env->map->z[i][j]);
}

void	ft_draw_vertical(t_fdf_env *env, t_fdf_coords current_point,
		int i, int j)

{
	t_fdf_coords	next_point;

	if (i >= env->map->y_max - 1)
		return ;
	next_point.x1 = current_point.x1
		- (env->var->spread * cos(0.5236 - env->var->angle));
	next_point.y1 = current_point.y1 + (env->var->spread * sin(0.5236
				- env->var->angle) - (env->map->z[i + 1][j]
				* env->var->mod_height));
	next_point.y1 += (env->map->z[i][j] * env->var->mod_height);
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (i < env->map->y_max)
		ft_secure_bresenham(env, current_point, 0xffffff, env->map->z[i][j]);
}

/* cycle through all the maps from coords (0,0) to coords (col_max, line_max)
 * calls the functions above to print at each given (i, j) point the line 
 * horizontal going to (i, j + 1) and the vertical one going to (i + 1, j) */

void	ft_draw_map(t_fdf_env *env)
{
	t_fdf_coords	start;
	t_fdf_coords	new_line;
	t_fdf_coords	current;
	int				i;
	int				j;

	i = 0;
	ft_get_start(env, &start);
	new_line = start;
	while (i < env->map->y_max)
	{
		j = 0;
		current = new_line;
		current.y1 -= env->map->z[i][j] * env->var->mod_height;
		while (j < env->map->x_max[i])
		{
			ft_draw_horizontal(env, current, i, j);
			ft_draw_vertical(env, current, i, j);
			j++;
			ft_get_new_point(env, &current, i, j);
		}
		i++;
		ft_get_new_line(env, &new_line, i);
	}
}
