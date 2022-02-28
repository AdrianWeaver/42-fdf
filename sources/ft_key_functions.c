/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:02:00 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 12:41:29 by aweaver          ###   ########.fr       */
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

int	ft_nuke_program(t_fdf_env *env)
{
	ft_free_map(env);
	if (env->img)
	{	
		if (env->img->img_id)
		{
			mlx_destroy_image(env->mlx_id, env->img->img_id);
		}
	}
	mlx_clear_window(env->mlx_id, env->mlx_window);
	mlx_destroy_window(env->mlx_id, env->mlx_window);
	mlx_destroy_display(env->mlx_id);
	free(env->mlx_id);
	exit (0);
	return (0);
}

int	ft_redraw(t_fdf_env *env)
{
	void		*save;

	save = env->img->img_id;
	ft_init_img(env, env->img);
	ft_draw_map(env);
	mlx_put_image_to_window(env->mlx_id, env->mlx_window, env->img->img_id,
		0, 0);
	mlx_destroy_image(env->mlx_id, save);
	ft_printf("redo\n");
	return (0);
	ft_make_square(env, env->img);
}
