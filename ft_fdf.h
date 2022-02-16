/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:57:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/16 08:00:56 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# ifndef MLX_FAILURE
#  define MLX_FAILURE "MLX couldn't establish a connection with a display"

# endif

# ifndef S_FDF_ENV
#  define S_FDF_ENV

typedef struct s_fdf_env
{
	void	*mlx_id;
	void	*mlx_window;
	int		window_w;
	int		window_h;
}				t_fdf_env;

typedef struct s_fdf_img
{
	void	*img_id;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fdf_img;
# endif
#endif
