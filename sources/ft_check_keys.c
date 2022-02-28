/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:11:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 10:34:27 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

static void	ft_make_square(t_fdf_env *env, t_fdf_img *img)
{
	int	x;
	int	y;

	x = 50;
	while (x < (env->window_w - 50))
	{
		y = 50;
		while (y < (env->window_h - 50))
		{
			ft_put_pixel_img(img, x, y, 0xff0000);
			y++;
		}
		x++;
	}
}

void	ft_boom(t_fdf_env *env)
{
	static int i;
	static int j;
	int mult;

	mult = 0;
	if (i < env->window_h)
	{
		if (j < env->window_w)
		{
			while (mult < 100)
			{
				ft_put_pixel_img(env->img, j, i, 0x0000ff);
				j++;
				mult++;
			}
		}
		else
		{
			i++;
			j = 0;
		}
	}
	ft_printf("Yes");
}

int	ft_check_keys(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_ESC)
		ft_nuke_program(env);
	if (keycode == KEY_PLUS)
	{
		if (env->var->spread == 1)
			env->var->spread = 5;
		else
			env->var->spread += 5;
		ft_redraw(env);
	}
	if (keycode == KEY_MINUS)
	{
		if (env->var->spread <= 5)
			env->var->spread = 1;
		else
			env->var->spread -= 5;
		ft_redraw(env);
	}
	if (keycode == KEY_RIGHT)
		ft_boom(env);
	if (keycode == KEY_UP)
		ft_make_square(env, env->img);
	return (0);
}
