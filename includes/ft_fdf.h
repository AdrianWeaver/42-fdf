/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:57:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/17 09:22:09 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include <fcntl.h>
# include "mlx.h"
# include "mlx_int.h"

# ifndef MLX_FAILURE
#  define MLX_FAILURE "MLX couldn't establish a connection with a display"

# endif

# ifndef S_FDF_ENV
#  define S_FDF_ENV

typedef struct s_fdf_img
{
	void	*img_id;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fdf_img;

typedef struct s_fdf_env
{
	void		*mlx_id;
	void		*mlx_window;
	int			window_w;
	int			window_h;
	t_fdf_img	*img;
}				t_fdf_env;

typedef struct s_fdf_map
{
	int toto;
}				t_fdf_map;

# endif

# ifndef FT_PUT_PIXEL_IMG
#  define FT_PUT_PIXEL_IMG

void	ft_put_pixel_img(t_fdf_img *img, int x, int y, int colour);

# endif

# ifndef FT_FDF_OPEN_MAP
#  define FT_FDF_OPEN_MAP

int	ft_fdf_open_map(char *file);

# endif

# ifndef KEYMAP_FDF
#  define KEYMAP_FDF

#  define KEY_ESC 0xff1b
#  define KEY_SPACE 0x20
#  define KEY_PLUS 0xffab
#  define KEY_MINUS	0xffad
#  define KEY_w	0x77
#  define KEY_a	0x61
#  define KEY_s	0x73
#  define KEY_d	0x64
#  define KEY_LEFT 0xff51
#  define KEY_UP 0xff52	
#  define KEY_RIGHT 0xff53
#  define KEY_DOWN 0xff54

# endif
#endif
