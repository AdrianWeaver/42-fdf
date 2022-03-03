/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:08:53 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/03 16:33:54 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

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
	if (abs(env->map->z_max - env->map->z_min) == 0)
	{
		env->var->step = 0;
		return ;
	}
	env->var->step = 255 / abs(env->map->z_max - env->map->z_min);
}

double	ft_get_argb(int a, int red, int green, int blue)
{
	if (red >= 255)
		red = 255;
	if (green >= 255)
		green = 255;
	if (blue >= 255)
		blue = 255;
	return (a << 24 | red << 16 | green << 8 | blue);
}

/* RED = (int)colour >> 16 & 0xff;
 * GREEN = (int)colour >> 8 & 0xff;
 * BLUE = (int)colour & 0xff;
 */

double	ft_bres_colour(t_fdf_env *env, int pixel_max, int incr, t_fdf_bresham b)
{
	int		gradient;
	int		red;
	int		green;
	int		blue;

	red = (int)env->var->colour >> 16 & 0xff;
	green = (int)env->var->colour >> 8 & 0xff;
	blue = (int)env->var->colour & 0xff;
	gradient = env->var->colour + (incr
		* ((env->var->step / pixel_max) * abs(b.z - b.z_next)));
	if (red > 0)
	{
		ft_printf("Debug de la honte red\n");
		red -= gradient;
		blue += gradient;
	}
	if (green > 0)
	{
		ft_printf("Debug de la honte green\n");
		green += gradient;
		blue -= gradient;
	}
	if (blue == 0)
	{
		if (incr == 1)
		{
			ft_printf("Debug de la honte blue green\n");
			green += gradient;
			blue -= gradient;
		}
		else if (incr == -1)
		{
			ft_printf("Debug de la honte blue red\n");
			red -= gradient;
			blue += gradient;
		}
	}
	return (ft_get_argb(1, red, green, blue));
}

void	ft_get_colour(t_fdf_env *env, int z)
{
	env->var->colour = MIN_COLOUR + (abs(z - env->map->z_min)
			* env->var->step);
}
