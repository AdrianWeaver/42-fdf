/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:30:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/26 10:47:37 by aweaver          ###   ########.fr       */
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

void	ft_bresenham_higher(t_fdf_env *env, t_fdf_coords line,
		t_fdf_bresham bresham, unsigned long int col)
{
	int	i;

	i = 0;
	while (i <= bresham.dx_start)
	{
		ft_put_pixel_img(env->img, line.x1, line.y1, col);
		i++;
		line.x1 += bresham.x_incr;
		bresham.ex -= bresham.dy;
		if (bresham.ex < 0)
		{
			line.y1 += bresham.y_incr;
			bresham.ex += bresham.dx;
		}
	}
}

void	ft_bresenham_lower(t_fdf_env *env, t_fdf_coords line,
		t_fdf_bresham bresham, unsigned long int col)
{
	int	i;

	i = 0;
	while (i <= bresham.dy_start)
	{
		ft_put_pixel_img(env->img, line.x1, line.y1, col);
		i++;
		line.y1 += bresham.y_incr;
		bresham.ey -= bresham.dx;
		if (bresham.ey < 0)
		{
			line.x1 += bresham.x_incr;
			bresham.ey += bresham.dy;
		}
	}
}

void	ft_bresenham(t_fdf_env *env, t_fdf_coords line, unsigned long int col)
{
	t_fdf_bresham	bresham;

	bresham.x_incr = 1;
	bresham.y_incr = 1;
	bresham.ex = abs(line.x2 - line.x1);
	bresham.ey = abs(line.y2 - line.y1);
	bresham.dx = 2 * bresham.ex;
	bresham.dy = 2 * bresham.ey;
	bresham.dx_start = bresham.ex;
	bresham.dy_start = bresham.ey;
	if (line.x1 > line.x2)
		bresham.x_incr = -1;
	if (line.y1 > line.y2)
		bresham.y_incr = -1;
	if (bresham.dx_start > bresham.dy_start)
		ft_bresenham_higher(env, line, bresham, col);
	if (bresham.dx_start <= bresham.dy_start)
		ft_bresenham_lower(env, line, bresham, col);
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
