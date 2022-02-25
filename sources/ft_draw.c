/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:10 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/25 17:57:48 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h> 
#include "libftprintf.h"
#include <stdio.h> 

int	ft_get_hypothenuse(int side_1, int side_2)
{
	return ((int)sqrt((side_1 * side_1) + (side_2 * side_2)));
}

void	ft_get_start(t_fdf_env *env, t_fdf_coords *coords)
{
	int		i;
	int		mean_x;
	double	angle_tan;
	double	angle_d;
	double	hypo;

	i = -1;
	mean_x = 0;
	if (env->map->y_max <= 1)
		env->map->y_max = 2;
	ft_printf("x_max = %d\n", env->map->x_max[env->map->y_max - 1]);
	while (++i < env->map->y_max)
		mean_x += env->map->x_max[i];
	mean_x /= env->map->y_max;
	ft_printf("mean_x = %d\n", mean_x);
	if (mean_x < 1)
		mean_x = 2;
	hypo = ft_get_hypothenuse(env->map->y_max / 2, mean_x /2);
	angle_tan = (env->map->y_max / 2) / (mean_x / 2);
	angle_d = atan(angle_tan);
	env->var->start_x = (env->window_w / 2) - (hypo * env->var->spread * cos(angle_d));
	env->var->start_y = (env->window_h / 2) - (hypo * env->var->spread * (sin(angle_d)));
	coords->x1 = env->var->start_x;
	coords->y1 = env->var->start_y;
	ft_printf("start_x = %d start_y = %d", env->var->start_x, env->var->start_y);
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
	/* to be deleted and swapped to coords struct */
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (j < env->map->x_max[i] - 1)
		ft_secure_bresenham(env, current_point, 0xffffff);
	//ft_bresenham(env, current_point, next_point, col); //aiming towards this
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
	//if (i != 0)
		next_point.y1 += env->map->z[i][j];
	current_point.x2 = next_point.x1;
	current_point.y2 = next_point.y1;
	if (i < env->map->y_max)
		ft_secure_bresenham(env, current_point, 0xffffff);
	//ft_bresenham(env, current_point, next_point, col); //aiming towards this
}
