/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:30:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/24 10:18:54 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"
#include <math.h>

//int		ft_check_limits(t_fdf_env *env, t_fdf_projection *proj)
//{
	//if (proj->x1 > env->window_w || proj->x2 > env->window_w)
		//return (0);
	//if (proj->x1 < 0 || proj->x2 < 0)
		//return (0);
	//if (proj->x1 < 0 || proj->x2 < 0)
		//return (0);
	//if (proj->y1 > env->window_h || proj->y2 > env->window_h)
		//return (0);
	//else
		//ft_bresenham(t_fdf_projection *proj);

void	ft_bresenham(t_fdf_env *env, t_fdf_line line)
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
	/* only for testing 
	x1 += 250;
	x2 += 250;
	y1 += 250;
	y2 += 250;
	only for testing */

	if (x1 > x2)
		Xincr = -1;
	if (y1 > y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			ft_put_pixel_img(env->img, x1, y1, 0xffffff);
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
			ft_put_pixel_img(env->img, x1, y1, 0xffffff);
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
	t_fdf_line	line_v;
	t_fdf_line	line_h;
	int			i;
	int			j;

	i = 0;
	env->var->angle = 0.52;
	ft_get_start(env);
	line_h.x1 = env->var->start_x; 
	line_h.y1 = env->var->start_y;
	line_v.x1 = env->var->start_x; 
	line_v.y1 = env->var->start_y;
	ft_printf("line_h.x1 = %d line_h.y1 = %d\n", line_h.x1, line_h.y1);
	ft_printf("line_v.x1 = %d line_v.y1 = %d\n", line_v.x1, line_v.y1);
	while (i < env->map->y_max)
	//while (i < 10)
	{
		j = 0;
		line_v.x1 = line_h.x1;
		line_v.y1 = line_h.y1;
		while (j < env->map->x_max[i])
		{
	//printing horizontal
			line_h.x2= line_h.x1 + env->var->spread * cos(env->var->angle);
			line_h.y2= line_h.y1 + env->var->spread * sin(env->var->angle) - env->map->z[i][j];
			if (j != 0)
				line_h.y2 += env->map->z[i][j - 1];
			if (j < env->map->x_max[i] - 1)
				ft_bresenham(env, line_h);
			line_h.x1 = line_h.x2;
			line_h.y1 = line_h.y2;
	//printing vertical
			if (i < env->map->y_max - 1)
			{
				line_v.x2 = line_v.x1 - env->var->spread * cos(env->var->angle);
				line_v.y2 = line_v.y1 + env->var->spread * sin(env->var->angle) - env->map->z[i + 1][j];
				//if (i != 0)
					//line_h.y2 += env->map->z[i][j];
				ft_bresenham(env, line_v);
				line_v.x1 = line_h.x2;
				line_v.y1 = line_h.y2;
			}
			j++;
		}
		line_h.x1 = env->var->start_x - (env->var->spread * i * cos(env->var->angle));
		line_h.y1 = env->var->start_y + (env->var->spread * i * sin(env->var->angle)); 
		i++;
	}
}

/* following code is the previous atempt at printing the whole map
   int	x;
   int	y;

   y = 0;
   while (y < env->map->y_max - 1)
   {
   x = 0;
   while (x < env->map->x_max[y] - 1)
   {
   ft_bresenham(env, x, (y - env->map->z[y][x]), x + 1,
   ((y + 1) - env->map->z[y + 1][x + 1]));
   x++;
   }
   y++;
   }
   ft_printf("nope");
   }
   */

