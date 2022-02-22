/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:57:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/22 08:17:34 by aweaver          ###   ########.fr       */
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
	void	*img_str;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fdf_img;

typedef struct s_fdf_map
{
	size_t			*x_max;
	size_t			y_max;
	int				**z;
}				t_fdf_map;

typedef struct s_fdf_env
{
	void		*mlx_id;
	void		*mlx_window;
	int			window_w;
	int			window_h;
	t_fdf_img	*img;
	t_fdf_map	*map;
}				t_fdf_env;

typedef struct s_fdf_str
{
	char				*str;
	struct s_fdf_str	*next;
}				t_fdf_str;

# endif

# ifndef FT_PUT_PIXEL_IMG
#  define FT_PUT_PIXEL_IMG

void	ft_put_pixel_img(t_fdf_img *img, int x, int y, int colour);

# endif

# ifndef FT_FDF_OPEN_MAP
#  define FT_FDF_OPEN_MAP

int		ft_fdf_open_map(char *file, t_fdf_env *env);

# endif

# ifndef KEYMAP_FDF
#  define KEYMAP_FDF

#  define KEY_ESC 0xff1b
#  define KEY_SPACE 0x20
#  define KEY_PLUS 0xffab
#  define KEY_MINUS	0xffad
#  define KEY_W	0x77
#  define KEY_A	0x61
#  define KEY_S	0x73
#  define KEY_D	0x64
#  define KEY_LEFT 0xff51
#  define KEY_UP 0xff52	
#  define KEY_RIGHT 0xff53
#  define KEY_DOWN 0xff54

void	ft_free_map(t_fdf_env *env);
void	ft_free_str(t_fdf_str *gnl);

/* KEYHOOK FUNCTIONS */

int		ft_check_keys(int keycode, t_fdf_env *env);
int		ft_nuke_program(t_fdf_env *env);

# endif
#endif
