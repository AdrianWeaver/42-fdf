/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 07:16:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/16 08:04:54 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include "libftprintf.h"
#include "ft_fdf.h"

void	ft_pixel_img_put(t_fdf_img *img, int x, int y, int color)
{
	char	*dst_pixel;

	dst_pixel = img->img_ptr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*dst_pixel = color;
}

int	main(void)
{
	t_fdf_env	env;
	t_fdf_img	img;

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
	img.img_ptr = mlx_get_data_addr(img.img_id, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	//mlx_pixel_put(mlx, mlx_window, 250, 250, 0x00ffffff);
	mlx_put_image_to_window(env.mlx_id, env.mlx_window, img.img_id, 0, 0);
	mlx_loop(env.mlx_id);
	return (0);
}
