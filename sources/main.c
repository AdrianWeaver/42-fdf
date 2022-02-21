/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 07:16:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/21 15:51:35 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "libftprintf.h"
#include "ft_fdf.h"
#include "get_next_line.h"

int	main(void)
{
	t_fdf_env	env;
	t_fdf_img	img;
	int			x;
	int			y;

	x = 50;
	env.img = &img;
	env.window_w = 500;
	env.window_h = 500;
	env.mlx_id = mlx_init();
	if (env.mlx_id == 0)
	{
		ft_printf("%s\n", MLX_FAILURE);
		return (0);
	}
	env.mlx_window = mlx_new_window(env.mlx_id, env.window_w, env.window_h,
			"My custom window");
	if (env.mlx_window == 0)
		return (0);
	img.img_id = mlx_new_image(env.mlx_id, env.window_w, env.window_h);
	img.img_str = mlx_get_data_addr(img.img_id, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	ft_fdf_open_map("test_maps/42.fdf", &env);
	while (x < (env.window_w - 50))
	{
		y = 50;
		while (y < (env.window_h - 50))
		{
			ft_put_pixel_img(&img, x, y, 0xff0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(env.mlx_id, env.mlx_window, img.img_id, 0, 0);
	mlx_hook(env.mlx_window, 3, 1L << 1, &ft_check_keys, &env);
	mlx_hook(env.mlx_window, 17, 0, &ft_nuke_program, &env);
	mlx_loop(env.mlx_id);
	return (0);
}
