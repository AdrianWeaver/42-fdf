/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:30:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/25 17:13:25 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"
#include <math.h>

void	ft_secure_bresenham(t_fdf_env *env, t_fdf_coords line,
		unsigned long int col)
{
	if (line.x1 > env->window_w || line.x2 > env->window_w)
		return ;
	if (line.x1 < 0 || line.x2 < 0)
		return ;
	if (line.x1 < 0 || line.x2 < 0)
		return ;
	if (line.y1 > env->window_h || line.y2 > env->window_h)
		return ;
	else
		ft_bresenham(env, line, col);
}

void	ft_bresenham(t_fdf_env *env, t_fdf_coords line, unsigned long int col)
{
	int	ex;
	int	ey;
	int	dx;
	int	dy;
	int	Dx;
	int	Dy;
	int	Xincr;
	int	Yincr;
	int	i;
	int	x1;
	int	y1;
	int	x2;
	int	y2;


	x1 = line.x1; 
	y1 = line.y1; 
	x2 = line.x2; 
	y2 = line.y2; 
	i = 0;
	Xincr = 1;
	Yincr = 1;
	ex = abs(x2 - x1);
	ey = abs(y2 - y1);
	dx = 2 * ex;
	dy = 2 * ey;
	Dx = ex;
	Dy = ey;

	if (x1 > x2)
		Xincr = -1;
	if (y1 > y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			ft_put_pixel_img(env->img, x1, y1, col);
			i++;
			x1 += Xincr;
			ex -= dy;
			if (ex < 0)
			{
			y1 += Yincr;
			ex += dx;
			}
		}
	}
	if (Dx <= Dy)
	{
		while (i <= Dy)
		{
			ft_put_pixel_img(env->img, x1, y1, col);
			i++;
			y1 += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += Xincr;
				ey += dy;
			}
		}
	}
}

void	ft_draw_map(t_fdf_env *env)
{
	t_fdf_coords	start;
	t_fdf_coords	new_line;
	t_fdf_coords	current;
	int				i;
	int				j;

	i = 0;
	ft_get_start(env, &start);
	new_line = start;
	while (i < env->map->y_max)
	{
		j = 0;
		current = new_line;
		current.y1 -= env->map->z[i][j];
		while (j < env->map->x_max[i])
		{
			ft_draw_horizontal(env, current, i, j);
			ft_draw_vertical(env, current, i, j);
			j++;
			ft_get_new_point(env, &current, i, j);
		}
		i++;
		ft_get_new_line(env, &new_line, i);
	}
}
