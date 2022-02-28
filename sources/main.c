/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 07:16:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 17:31:33 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "libftprintf.h"
#include "ft_fdf.h"
#include "get_next_line.h"

void	ft_init_var(t_fdf_env *env, t_fdf_var *var)
{
	var->mod_height = 1;
	var->spread = 10;
	var->angle = 0.5236;
	var->center_x = env->window_w / 2;
	var->center_y = env->window_h / 2;
	env->var = var;
}

void	ft_init_img(t_fdf_env *env, t_fdf_img *img)
{
	img->img_id = mlx_new_image(env->mlx_id, env->window_w, env->window_h);
	img->img_str = mlx_get_data_addr(img->img_id, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	env->img = img;
}

void	t_fdf_init_env(t_fdf_env *env)
{
	env->window_w = 800;
	env->window_h = 800;
	env->mlx_id = mlx_init();
	if (env->mlx_id == 0)
	{
		ft_printf("%s\n", MLX_FAILURE);
		exit(0);
	}
}

int	main_2(char **argv)
{
	t_fdf_env	env;
	t_fdf_img	img;
	t_fdf_var	var;

	t_fdf_init_env(&env);
	if (env.mlx_id == 0)
	{
		ft_printf("%s\n", MLX_FAILURE);
		return (0);
	}
	env.mlx_window = mlx_new_window(env.mlx_id, env.window_w, env.window_h,
			argv[1]);
	if (env.mlx_window == 0)
		return (0);
	ft_init_img(&env, &img);
	ft_init_var(&env, &var);
	ft_fdf_open_map(argv[1], &env);
	ft_get_proportion(&env);
	ft_draw_map(&env);
	mlx_put_image_to_window(env.mlx_id, env.mlx_window, img.img_id, 0, 0);
	mlx_hook(env.mlx_window, 3, 1L << 1, &ft_check_keys, &env);
	mlx_hook(env.mlx_window, 17, 0, &ft_nuke_program, &env);
	//mlx_hook(env.mlx_window, 25, 0, &ft_redraw, &env);
	mlx_loop(env.mlx_id);
	exit (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf(RED"Please provide a map to display :)\n");
		return (0);
	}
	if (argc > 2)
	{
		ft_printf(RED"That's cheeky! Please only provide a map to display!\n");
		return (0);
	}
	main_2(argv);
}
