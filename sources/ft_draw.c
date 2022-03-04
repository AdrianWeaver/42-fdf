/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:10 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/04 13:32:19 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h> 
#include "libftprintf.h"
#include <stdio.h> 

/* secure bresenham called in the followed functions is just a safety to
 * avoid writing out of the boundaries of the image 					*/

void	ft_draw_horizontal(t_fdf_env *env, t_fdf_coords to_draw,
		int i, int j)
{
	to_draw.x2 = to_draw.x1 + env->var->spread
		* cos(env->var->o + env->var->angle);
	if (j < env->map->x_max[i] - 1)
	{
		to_draw.y2 = to_draw.y1 + env->var->spread
			* sin(env->var->o + env->var->angle) - (env->map->z[i][j + 1]
				* env->var->mod_height);
		to_draw.y1 -= (env->map->z[i][j] * env->var->mod_height);
		env->var->colour = ft_get_colour(env, env->map->z[i][j]);
		ft_secure_bresenham(env, to_draw, env->var->colour,
			env->map->z[i][j]);
	}
}
//ft_secure_bresenham(env, current_point, 0xffd700, env->map->z[i][j]);

void	ft_draw_vertical(t_fdf_env *env, t_fdf_coords to_draw,
		int i, int j)

{
	if (i >= env->map->y_max - 1)
		return ;
	to_draw.x2 = to_draw.x1 - env->var->spread
		* cos(env->var->o - env->var->angle);
	if (i < env->map->y_max)
	{
		to_draw.y2 = to_draw.y1 + (env->var->spread
				* sin(env->var->o - env->var->angle)) - (env->map->z[i + 1][j]
				* env->var->mod_height);
	to_draw.y1 -= (env->map->z[i][j] * env->var->mod_height);
		env->var->colour = ft_get_colour(env, env->map->z[i][j]);
		ft_secure_bresenham(env, to_draw, env->var->colour, env->map->z[i][j]);
	}
}
//ft_secure_bresenham(env, to_draw, 0x0057b7, env->map->z[i][j]);

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
