/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:30:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/22 11:42:25 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int		ft_check_limits(t_fdf_env *env, t_fdf_projection *proj)
{
	if (proj->x1 > env->window_w || proj->x2 > env->window_w)
		return (0);
	if (proj->x1 < 0 || proj->x2 < 0)
		return (0);
	if (proj->x1 < 0 || proj->x2 < 0)
		return (0);
	if (proj->y1 > env->window_h || proj->y2 > env->window_h)
		return (0);
	else
		ft_bresenham(t_fdf_projection *proj);

void	ft_bresenham(size_t x1, size_t y1)
{
}

void	draw_map(t_fdf_env *env)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < y_max - 1)
	{
		x = 0;
		while (x < x_max - 1)
		{
			ft_bresenham(x, (y + env->z[x][y]), x + 1,
					(y + 1 + env->z[x + 1][y + 1]));
			x++;
		}
		y++;
	}
}

