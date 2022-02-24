/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:29:10 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/24 09:12:31 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h> 
#include "libftprintf.h"

void	ft_get_start(t_fdf_env *env)
{
	int		i;
	int		mean_x;
	double	angle_tan;
	double	angle_d;

	i = 0;
	mean_x = 0;
	//env->var->start_x = 250;
	//env->var->start_y = 250;
	//return ;
//}
	if (env->map->y_max <= 1)
		env->map->y_max = 2;
	while (i < env->map->x_max[env->map->y_max])
	{
		mean_x += env->map->x_max[i];
		i++;
	}
	mean_x /= env->map->y_max;
	if (mean_x < 1)
		mean_x = 2;
	angle_tan = (env->map->y_max / 2) / (mean_x / 2);
	angle_d = atan(angle_tan);
	env->var->start_x = (env->window_w / 2) - (((mean_x / 2) + (env->map->y_max / 2)) * env->var->spread * (cos(angle_d)));
	env->var->start_y = (env->window_h / 2) - (((mean_x / 2) + (env->map->y_max / 2)) * env->var->spread * (sin(angle_d)));
	ft_printf("start_x = %d\n", env->var->start_x);
	ft_printf("start_y = %d\n", env->var->start_y);
}

//void	ft_draw_horizontal(t_fdf_line line)
//{
//
//}
//
//void	ft_draw_vertical(t_fdf_line line)
//{
//
//}
