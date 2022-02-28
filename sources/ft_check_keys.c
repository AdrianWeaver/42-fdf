/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:11:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 13:22:40 by aweaver          ###   ########.fr       */
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

void	ft_check_rotate(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_A)
	{
		env->var->angle += 0.7854;
		if (env->var->angle >= 6)
			env->var->angle = 0.5236;
		ft_redraw(env);
	}
	if (keycode == KEY_D)
	{
		env->var->angle -= 0.7854;
		if (env->var->angle <= 0)
			env->var->angle = 0.7854;
	}
	if (keycode == KEY_W)
		env->var->mod_height += 1;
	if (keycode == KEY_S)
		env->var->mod_height -= 1;
	ft_redraw(env);
}

void	ft_check_translate(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_LEFT)
		env->var->center_x -= env->var->spread;
	if (keycode == KEY_RIGHT)
		env->var->center_x += env->var->spread;
	if (keycode == KEY_UP)
		env->var->center_y -= env->var->spread;
	if (keycode == KEY_DOWN)
		env->var->center_y += env->var->spread;
	ft_redraw(env);
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
	if (keycode == KEY_UP)
		ft_make_square(env, env->img);
	ft_check_translate(keycode, env);
	ft_check_rotate(keycode, env);
	return (0);
}
