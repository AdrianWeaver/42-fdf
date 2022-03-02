/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:30:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/02 09:48:44 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"
#include <math.h>

/* securing the limits of the image so the program does not try to write
 * out of the set boundaries											*/

void	ft_secure_bresenham(t_fdf_env *env, t_fdf_coords line,
		unsigned long int col, int z)
{
	if (line.x1 > env->window_w || line.x2 > env->window_w)
		return ;
	if (line.x1 <= 0 || line.x2 <= 0)
		return ;
	if (line.y1 <= 0 || line.y2 <= 0)
		return ;
	if (line.y1 >= env->window_h || line.y2 >= env->window_h)
		return ;
	else
		ft_bresenham(env, line, col, z);
}

void	ft_bresenham_higher(t_fdf_env *env, t_fdf_coords line,
		t_fdf_bresham bresham, unsigned long int col, int z)
{
	int	i;
	(void)col; //to be deleted
	(void)z;

	i = 0;
	while (i < bresham.dx_start)
	{
		ft_put_pixel_img(env->img, line.x1, line.y1, col);
		//ft_put_pixel_img(env->img, line.x1, line.y1, ft_get_colour(env, z, i));
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
		t_fdf_bresham bresham, unsigned long int col, int z)
{
	int	i;
	(void)col; //to be deleted
	(void)z;

	i = 0;
	while (i <= bresham.dy_start)
	{
		ft_put_pixel_img(env->img, line.x1, line.y1, col);
		//ft_put_pixel_img(env->img, line.x1, line.y1, ft_get_colour(env, z, i));
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

/* this function's purpose is to draw the most efficient approximation of 
 * a straight line using pixels (int coords) instead of line equation (float) */

void	ft_bresenham(t_fdf_env *env, t_fdf_coords line, unsigned long int col, int z)
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
		ft_bresenham_higher(env, line, bresham, col, z);
	if (bresham.dx_start <= bresham.dy_start)
		ft_bresenham_lower(env, line, bresham, col, z);
}
