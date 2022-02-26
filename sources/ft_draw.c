/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:10 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/26 11:00:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h> 
#include "libftprintf.h"
#include <stdio.h> 

void	ft_get_start(t_fdf_env *env, t_fdf_coords *coords)
{
	int		i;
	int		mean_x;

	i = -1;
	mean_x = 0;
	if (env->map->y_max <= 1)
		env->map->y_max = 2;
	while (++i < env->map->y_max)
		mean_x += env->map->x_max[i];
	mean_x /= env->map->y_max;
	if (mean_x < 1)
		mean_x = 2;
	coords->x1 = (env->window_w / 2) - (mean_x / 2 * env->var->spread
			* cos(env->var->angle));
	coords->x1 += env->map->y_max / 2 * env->var->spread
		* cos(env->var->angle);
	coords->y1 = (env->window_h / 2) - (env->map->y_max / 2 * env->var->spread
			* sin(env->var->angle));
	coords->y1 -= mean_x / 2 * env->var->spread * sin(env->var->angle);
	env->var->start_x = coords->x1;
	env->var->start_y = coords->y1;
}

void	ft_get_new_point(t_fdf_env *env, t_fdf_coords *current,
		int i, int j)
{
	current->x1 += env->var->spread * cos(env->var->angle);
	current->y1 += env->var->spread * sin(env->var->angle) - env->map->z[i][j];
	if (j > 0)
		current->y1 += env->map->z[i][j - 1];
}

void	ft_get_new_line(t_fdf_env *env, t_fdf_coords *new_line, int i)
{
	if (i >= env->map->y_max)
		return ;
	new_line->x1 -= env->var->spread * cos(env->var->angle);
	new_line->y1 += env->var->spread * sin(env->var->angle);
}

void	ft_draw_horizontal(t_fdf_env *env, t_fdf_coords current_point,
		int i, int j)
{
	t_fdf_coords	next_point;

	if (j > env->map->x_max[i])
		return ;
	next_point.x1 = current_point.x1 + env->var->spread * cos(env->var->angle);
	next_point.y1 = current_point.y1 + env->var->spread * sin(env->var->angle)
		- env->map->z[i][j + 1];
	next_point.y1 += env->map->z[i][j];
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (j < env->map->x_max[i] - 1)
		ft_secure_bresenham(env, current_point, 0xffffff);
}

void	ft_draw_vertical(t_fdf_env *env, t_fdf_coords current_point,
		int i, int j)

{
	t_fdf_coords	next_point;

	if (i >= env->map->y_max - 1)
		return ;
	next_point.x1 = current_point.x1 - env->var->spread * cos(env->var->angle);
	next_point.y1 = current_point.y1 + (env->var->spread * sin(env->var->angle)
			- env->map->z[i + 1][j]);
	next_point.y1 += env->map->z[i][j];
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (i < env->map->y_max)
		ft_secure_bresenham(env, current_point, 0xffffff);
}
