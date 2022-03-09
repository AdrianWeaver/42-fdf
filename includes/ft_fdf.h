/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:57:22 by aweaver           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/08 10:02:02 by aweaver          ###   ########.fr       */
=======
/*   Updated: 2022/03/07 11:05:03 by aweaver          ###   ########.fr       */
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
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
# ifndef FDF_COLOURS
#  define FDF_COLOURS
#  define MIN_COLOUR 0xff0000
#  define MAX_COLOUR 0x00ff00

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
	int			*x_max;
	int			y_max;
	int			**z;
	int			z_max;
	int			z_min;
}				t_fdf_map;

typedef struct s_fdf_str
{
	char				*str;
	struct s_fdf_str	*next;
}				t_fdf_str;

typedef struct s_fdf_coords
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}				t_fdf_coords;

typedef struct s_fdf_var
{
	int		mod_height;
	int		spread;
	int		center_x;
	int		center_y;
	int		start_x;
	int		start_y;
	int		start_spread;
	double	step;
	double	colour;
	double	o;
	double	angle;
}				t_fdf_var;

typedef struct s_fdf_env
{
	void		*mlx_id;
	void		*mlx_window;
	int			window_w;
	int			window_h;
	t_fdf_img	*img;
	t_fdf_map	*map;
	t_fdf_var	*var;
}				t_fdf_env;

typedef struct s_fdf_col
{
	int	red;
	int	green;
	int	blue;
}				t_fdf_col;

typedef struct s_fdf_bresham
{
	int			ex;
	int			ey;
	int			dx;
	int			dy;
	int			dx_start;
	int			dy_start;
	int			x_incr;
	int			y_incr;
	int			z;
	int			z_next;
	t_fdf_col	col;
	double		i;
}				t_fdf_bresham;

# endif

# ifndef FT_FDF_OPEN_MAP
#  define FT_FDF_OPEN_MAP

int		ft_fdf_open_map(char *file, t_fdf_env *env);

# endif

# ifndef FT_INIT_IMG
#  define FT_INIT_IMG

void	ft_init_img(t_fdf_env *env, t_fdf_img *img);

# endif

/* DRAWING FUNCTIONS */

# ifndef FT_PUT_PIXEL_IMG
#  define FT_PUT_PIXEL_IMG

void	ft_put_pixel_img(t_fdf_img *img, int x, int y, int colour);
void	ft_bresenham(t_fdf_env *env, t_fdf_coords line,	int z, int z_next);
void	ft_secure_bresenham(t_fdf_env *env, t_fdf_coords line, int z, int z_n);

# endif
# ifndef FT_DRAW_MAP
#  define FT_DRAW_MAP

void	ft_draw_map(t_fdf_env *env);

# endif

void	ft_draw_horizontal(t_fdf_env *env, t_fdf_coords current_point,
			int i, int j);

void	ft_draw_vertical(t_fdf_env *env, t_fdf_coords current_point,
			int i, int j);

# ifndef FT_GET_START
#  define FT_GET_START

/* FUNCTIONS GET */

void	ft_get_start(t_fdf_env *env, t_fdf_coords *coords);
void	ft_get_new_line(t_fdf_env *env, t_fdf_coords *current, int i);
void	ft_get_new_point(t_fdf_env *env, t_fdf_coords *current,	int i, int j);
void	ft_get_z_max(t_fdf_env *env);
void	ft_get_z_min(t_fdf_env *env);
void	ft_get_step(t_fdf_env *env);
double	ft_get_argb(int a, int r, int g, int b);
double	ft_get_gradient(t_fdf_env *env, t_fdf_bresham b, int px_max, double i);
void	ft_get_proportion(t_fdf_env *env);
double	ft_get_colour(t_fdf_env *env, int z);
double	ft_bres_colour(t_fdf_env *env, int px_max, t_fdf_bresham b);

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
#  define KEY_R 0x72
#  define KEY_LEFT 0xff51
#  define KEY_UP 0xff52	
#  define KEY_RIGHT 0xff53
#  define KEY_DOWN 0xff54

/* FREE MEMORY FUNCTIONS */

void	ft_free_map(t_fdf_env *env);
void	ft_free_str(t_fdf_str *gnl);
void	ft_nuke_empty(t_fdf_env *env);
<<<<<<< HEAD
void	ft_nuke_wrong_fd(t_fdf_env *env);
=======
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848

/* KEYHOOK FUNCTIONS */

int		ft_check_keys(int keycode, t_fdf_env *env);
int		ft_nuke_program(t_fdf_env *env);
int		ft_redraw(t_fdf_env *env);
int		ft_reset(t_fdf_env *env);

# endif
#endif
