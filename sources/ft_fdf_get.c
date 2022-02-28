/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 07:52:36 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 11:07:52 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_fdf.h"

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
	coords->x1 = env->var->center_x - (mean_x / 2 * env->var->spread
			* cos(env->var->angle));
	coords->x1 += env->map->y_max / 2 * env->var->spread
		* cos(env->var->angle);
	coords->y1 = env->var->center_y - (env->map->y_max / 2 * env->var->spread
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
