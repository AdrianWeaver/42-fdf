/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:11:34 by aweaver           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/08 09:32:51 by aweaver          ###   ########.fr       */
=======
/*   Updated: 2022/03/02 10:38:49 by aweaver          ###   ########.fr       */
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

void	ft_check_rotate(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_A)
	{
		env->var->o = 0.5236;
		env->var->angle += 0.2618;
		if (env->var->angle >= 6)
<<<<<<< HEAD
			env->var->angle = 0;
=======
			env->var->angle = 0.5236;
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
		ft_redraw(env);
	}
	if (keycode == KEY_D)
	{
		env->var->o = 0.5236;
		env->var->angle -= 0.2618;
<<<<<<< HEAD
		if (env->var->angle < 0)
			env->var->angle = 5.7596;
=======
		if (env->var->angle <= 0.5)
			env->var->angle = 6.2832;
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
		ft_redraw(env);
	}
	if (keycode == KEY_SPACE)
	{
		env->var->angle = 0;
		env->var->o = 0;
		ft_redraw(env);
	}
}

void	ft_change_height(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_W)
	{
		env->var->mod_height += 1;
		ft_redraw(env);
	}
	if (keycode == KEY_S)
	{
		env->var->mod_height -= 1;
		ft_redraw(env);
	}
}

void	ft_check_translate(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_LEFT)
	{
		env->var->center_x -= env->var->spread;
		ft_redraw(env);
	}
	if (keycode == KEY_RIGHT)
	{
		env->var->center_x += env->var->spread;
		ft_redraw(env);
	}
	if (keycode == KEY_UP)
	{
		env->var->center_y -= env->var->spread;
		ft_redraw(env);
	}
	if (keycode == KEY_DOWN)
	{
		env->var->center_y += env->var->spread;
		ft_redraw(env);
	}
}

void	ft_check_zoom(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_PLUS)
	{
		if (env->var->spread == 1)
			env->var->spread = 2;
		else
			env->var->spread += 1;
		ft_redraw(env);
	}
	if (keycode == KEY_MINUS)
	{
		if (env->var->spread <= 1)
			env->var->spread = 1;
		else
			env->var->spread -= 1;
		ft_redraw(env);
	}
}

int	ft_check_keys(int keycode, t_fdf_env *env)
{
	if (keycode == KEY_ESC)
		ft_nuke_program(env);
	if (keycode == KEY_R)
		ft_reset(env);
	ft_check_zoom(keycode, env);
	ft_check_translate(keycode, env);
	ft_check_rotate(keycode, env);
	ft_change_height(keycode, env);
	return (0);
}
