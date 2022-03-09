/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:51:23 by aweaver           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/08 10:20:47 by aweaver          ###   ########.fr       */
=======
/*   Updated: 2022/03/02 13:12:50 by aweaver          ###   ########.fr       */
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

/* Morgan would be proud because man that's some neat free here (got it?) */

void	ft_free_map(t_fdf_env *env)
{
	int	i;

	i = 0;
	while (i < env->map->y_max)
	{
		free(env->map->z[i]);
		i++;
	}
	free(env->map->z);
	free(env->map->x_max);
	free(env->map);
}

void	ft_free_str(t_fdf_str *gnl)
{
	t_fdf_str	*save;

	while (gnl)
	{
		save = gnl;
		gnl = gnl->next;
		free(save);
	}
}

<<<<<<< HEAD
void	ft_nuke_wrong_fd(t_fdf_env *env)
{
	if (env->img)
	{	
		if (env->img->img_id)
		{
			mlx_destroy_image(env->mlx_id, env->img->img_id);
		}
	}
	mlx_destroy_window(env->mlx_id, env->mlx_window);
	mlx_destroy_display(env->mlx_id);
	free(env->mlx_id);
	ft_printf("The progran could not open the map you provided\n");
	exit (-1);
}

=======
>>>>>>> d87b4cc571e9795d089779e7d81b33522b087848
void	ft_nuke_empty(t_fdf_env *env)
{
	free(env->map);
	if (env->img)
	{	
		if (env->img->img_id)
		{
			mlx_destroy_image(env->mlx_id, env->img->img_id);
		}
	}
	mlx_destroy_window(env->mlx_id, env->mlx_window);
	mlx_destroy_display(env->mlx_id);
	free(env->mlx_id);
	ft_printf("The map you provided was empty\n");
	exit (0);
}
