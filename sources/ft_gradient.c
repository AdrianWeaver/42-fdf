/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:08:53 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/07 11:06:56 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"
#include <stdio.h>

int	ft_up_colour(double colour, int bitshift, double to_add)
{
	int	focus;

	focus = ((int)colour >> bitshift & 0xff);
	focus += to_add;
	if (focus > 255)
		return (255);
	else if (focus < 0)
		return (0);
	else
		return (focus);
}

double	ft_bres_colour_2(t_fdf_env *env, t_fdf_bresham b, double slop,
		double gradient)
{
	if (b.col.blue == 255)
	{
		b.col.blue = ft_up_colour(env->var->colour, 0, - (slop * gradient));
		if (b.z < b.z_next)
			b.col.green = ft_up_colour(env->var->colour, 8, (slop * gradient));
		else if (b.z > b.z_next)
			b.col.red = ft_up_colour(env->var->colour, 16, (slop * gradient));
	}	
	else if (b.col.red > 0 && b.col.green == 0)
	{
		b.col.red = ft_up_colour(env->var->colour, 16, - (slop * gradient));
		b.col.blue = ft_up_colour(env->var->colour, 0, (slop * gradient));
	}
	else if (b.col.green > 0 && b.col.red == 0)
	{
		b.col.green = ft_up_colour(env->var->colour, 8, (slop * gradient));
		b.col.blue = ft_up_colour(env->var->colour, 0, - (slop * gradient));
	}
	return (ft_get_argb(1, b.col.red, b.col.green, b.col.blue));
}

double	ft_bres_colour(t_fdf_env *env, int pixel_max, t_fdf_bresham b)
{
	t_fdf_col	col;
	double		gradient;
	double		slope;

	slope = 1.0;
	if (b.z > b.z_next)
		slope = -1.0;
	col.red = (int)env->var->colour >> 16 & 0xff;
	col.green = (int)env->var->colour >> 8 & 0xff;
	col.blue = (int)env->var->colour & 0xff;
	gradient = ft_get_gradient(env, b, pixel_max, b.i) / 2;
	b.col = col;
	return (ft_bres_colour_2(env, b, slope, gradient));
}

double	ft_get_colour(t_fdf_env *env, int z)
{
	double	colour;
	int		z_mid;

	z_mid = env->map->z_max
		- ((env->map->z_max - env->map->z_min) / 2);
	if (z <= z_mid)
	{
		colour = MIN_COLOUR;
		colour -= (((int)((float)z * env->var->step)) << 16);
		colour += (((int)((float)z * env->var->step)));
	}
	else if (z > z_mid)
	{
		colour = MAX_COLOUR;
		colour = ft_get_argb(1, (int)colour >> 16,
				ft_up_colour(colour, 8, - ((env->map->z_max - z)
						* env->var->step)),
				ft_up_colour(colour, 0, ((env->map->z_max - z)
						* env->var->step)));
	}
	return (colour);
}
