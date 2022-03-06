/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:08:53 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/06 21:01:20 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"
#include <stdio.h>

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
	double argb;
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
	printf("get argb argb = %f\n", argb);
	printf("Function get argb red = %d\n", (int)argb >> 16 & 0xff);
	printf("Function get argb green = %d\n", (int)argb >> 8 & 0xff);
	printf("Function get argb blue = %d\n", (int)argb & 0xff);
	return (argb);
}

/* RED = (int)colour >> 16 & 0xff;
 * GREEN = (int)colour >> 8 & 0xff;
 * BLUE = (int)colour & 0xff;
 */
double ft_get_gradient(t_fdf_env *env, t_fdf_bresham b, int pixel_max)
{
	int	blue_at_z;
	int	blue_at_next;
	int	colour_next;
	int	colour_z;

	colour_z = (int)env->var->colour;
	blue_at_z = colour_z & 0xff;
	colour_next = (int)ft_get_colour(env, b.z_next);
	printf("Function gradient >> colour_z = %d, colour_next = %d\n", colour_z,
			colour_next);
	blue_at_next = (colour_next & 0xff);
	printf("Function gradient blue_at_next = %d blue_at_z = %d\n", blue_at_next, blue_at_z);
	printf("Function gradient colour_z red = %d\n", (int)colour_z >> 16 & 0xff);
	printf("Function gradient colour_z green = %d\n", (int)colour_z >> 8 & 0xff);
	printf("Function gradient colour_z blue = %d\n", (int)colour_z & 0xff);
	printf("Function gradient colour_next red = %d\n", (int)colour_next >> 16 & 0xff);
	printf("Function gradient colour_next green = %d\n", (int)colour_next >> 8 & 0xff);
	printf("Function gradient colour_next blue = %d\n", (int)colour_next & 0xff);
	if (pixel_max == 0)
		return (blue_at_next - blue_at_z);
	return (((((double)blue_at_next) - ((double)blue_at_z)) / (double)pixel_max));
}

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

double	ft_bres_colour(t_fdf_env *env, int pixel_max, int incr,
		t_fdf_bresham b, int i)
{
	double		gradient;
	int		red;
	int		green;
	int		blue;
	int		slope;

	(void)incr;
	printf("\n\n==BRES COLOUR\n");
	slope = 1;
	if (b.z > b.z_next)
		slope = -1;
	red = (int)env->var->colour >> 16 & 0xff;
	green = (int)env->var->colour >> 8 & 0xff;
	blue = (int)env->var->colour & 0xff;
	gradient = ft_get_gradient(env, b, pixel_max);
	//gradient = (i * incr
		//* ((env->var->step / pixel_max) * abs(b.z - b.z_next)));
	if (blue == 255)
	{
		blue = ft_up_colour(env->var->colour, 0, - (i * slope * gradient));
		if (slope == 1)
		{
			green = ft_up_colour(env->var->colour, 8, (i * slope * gradient));
		}
		else if (slope == -1)
		{
			red = ft_up_colour(env->var->colour, 16, (i * slope * gradient));
		}
	}
	else if (red > 0 && green == 0)
	{
		red = ft_up_colour(env->var->colour, 16, - (i * slope * gradient));
		blue = ft_up_colour(env->var->colour, 0, (i * slope * gradient));
	}
	else if (green > 0 && red == 0)
	{
		green = ft_up_colour(env->var->colour, 8, - (i * slope * gradient));
		blue = ft_up_colour(env->var->colour, 0, (i * slope * gradient));
	}
	return (ft_get_argb(1, red, green, blue));
}

double	ft_get_colour(t_fdf_env *env, int z)
{
	double	colour;
	int	z_mid;

	z_mid = env->map->z_max
		- ((env->map->z_max - env->map->z_min) / 2);
	if (z < z_mid)
	{
		colour = MIN_COLOUR;
		colour -= (((int)((float)z * env->var->step)) << 16);
		colour += (((int)((float)z * env->var->step)));
	}
	else if (z == z_mid)
		colour = 0x0000ff;	
	else if (z > z_mid)
	{
		colour = MAX_COLOUR;
		colour -= (((int)(z * env->var->step)) << 8);
		colour += (((int)(z * env->var->step)));
	}
	printf("Function get colour red = %d\n", (int)colour >> 16 & 0xff);
	printf("Function get colour green = %d\n", (int)colour >> 8 & 0xff);
	printf("Function get colour blue = %d\n", (int)colour & 0xff);
	return (colour);
}
