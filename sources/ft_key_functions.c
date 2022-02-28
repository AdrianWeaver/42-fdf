/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:02:00 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 10:32:00 by aweaver          ###   ########.fr       */
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
	ft_printf("test 1\n");
	ft_free_map(env);
	ft_printf("test 2\n");
	if (env->img)
	{	
		ft_printf("test B1\n");
		if (env->img->img_id)
		{
			ft_printf("test B2\n");
			ft_printf("img id = %p ,img_str_address = %p, img_str = %s\n", env->img->img_id, env->img->img_str, env->img->img_str);
			mlx_destroy_image(env->mlx_id, env->img->img_id);
			ft_printf("test B3\n");
		}
	}
	ft_printf("test 3\n");
	mlx_clear_window(env->mlx_id, env->mlx_window);
	ft_printf("test 4\n");
	mlx_destroy_window(env->mlx_id, env->mlx_window);
	ft_printf("test 5\n");
	mlx_destroy_display(env->mlx_id);
	ft_printf("test 6\n");
	free(env->mlx_id);
	ft_printf("test 7\n");
	exit (0);
	return (0);
}

int	ft_redraw(t_fdf_env *env)
{
	void		*save;

	ft_printf("w_h = %d, w_w = %d\n", env->window_h, env->window_h);
	save = env->img->img_id;
	ft_init_img(env, env->img);
	ft_draw_map(env);
	mlx_put_image_to_window(env->mlx_id, env->mlx_window, env->img->img_id, 0, 0);
	mlx_destroy_image(env->mlx_id, save);
	ft_printf("redo\n");
	return (0);
	ft_make_square(env, env->img);
}
