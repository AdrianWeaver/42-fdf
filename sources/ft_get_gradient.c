/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_gradient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:11:37 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/07 10:55:07 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* gets the highest point of the map, used for the gradient coloring funct */

void	ft_get_z_max(t_fdf_env *env)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 0;
	while (i < env->map->y_max)
	{
		j = 0;
		while (j < env->map->x_max[i])
		{
			if (env->map->z[i][j] > ret)
				ret = env->map->z[i][j];
			j++;
		}
		i++;
	}
	if (ret > 255)
		ret = 255;
	env->map->z_max = ret;
	ft_get_z_min(env);
	ft_get_step(env);
}

void	ft_get_z_min(t_fdf_env *env)
{
	int	i;
	int	j;
	int	ret;

	ret = env->map->z_max;
	i = 0;
	while (i < env->map->y_max)
	{
		j = 0;
		while (j < env->map->x_max[i])
		{
			if (env->map->z[i][j] < ret)
				ret = env->map->z[i][j];
			j++;
		}
		i++;
	}
	if (ret < -255)
		ret = -255;
	env->map->z_min = ret;
}

void	ft_get_step(t_fdf_env *env)
{
	if (env->map->z_max - env->map->z_min == 0)
	{
		env->var->step = 0.0;
		return ;
	}
	env->var->step = 510.0 / ((float)env->map->z_max
			- (float)env->map->z_min);
}

double	ft_get_argb(int a, int red, int green, int blue)
{
	double	argb;

	if (red >= 255)
		red = 255;
	if (green >= 255)
		green = 255;
	if (blue >= 255)
		blue = 255;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	argb = a << 24 | red << 16 | green << 8 | blue;
	return (argb);
}

double	ft_get_gradient(t_fdf_env *env, t_fdf_bresham b, int pixel_max,
		double i)
{
	int	colour_next;
	int	colour_z;

	colour_z = (int)env->var->colour;
	colour_next = (int)ft_get_colour(env, b.z_next);
	if (pixel_max == 0)
	{
		return (((double)(abs(((int)colour_z >> 16 & 0xff) - ((int)colour_next
						>> 16 & 0xff)) + (abs(((int)colour_z >> 8 & 0xff)
						- ((int)colour_next >> 8 & 0xff))))) * i);
	}
	return (((double)(abs(((int)colour_z >> 16 & 0xff)
				- ((int)colour_next >> 16 & 0xff))
			+ (abs(((int)colour_z >> 8 & 0xff)
					- ((int)colour_next >> 8 & 0xff))))
		/ ((double)pixel_max) * i));
}
