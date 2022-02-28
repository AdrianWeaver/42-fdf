/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:08:53 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 20:34:14 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

unsigned long int	ft_get_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

unsigned long int	ft_get_colour(t_fdf_env *env, int z, int i)
{
	int					step;
	unsigned long int	colour;
	int					red;
	int					blue;
	int					green;
	(void)i;

	//colour = 0xffffff;
	//return (colour);
	step = 255 / env->map->z_max;
	if (env->map->z_max == 0)
	{
		colour = 0xffffff;
	}
	else if (z >= 0)
	{
		if (z < (env->map->z_max / 2))
		{
			blue = 255 - ((510 * z / (step)));
			red = 0;
			green = blue - 255;
		}
		colour = ft_get_argb(0, red, green, blue);
	}
	if (z < 0)
		colour = 0xffffff;
	return (colour);
}
