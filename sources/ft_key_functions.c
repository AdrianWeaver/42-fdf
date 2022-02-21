/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:02:00 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/21 15:09:34 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

int	ft_nuke_program(t_fdf_env *env)
{
	ft_free_map(env);
	if (env->img)
	{	
		if (env->img->img_id)
			mlx_destroy_image(env->mlx_id, env->img->img_id);
	}
	mlx_clear_window(env->mlx_id, env->mlx_window);
	mlx_destroy_window(env->mlx_id, env->mlx_window);
	mlx_destroy_display(env->mlx_id);
	free(env->mlx_id);
	exit (0);
	return (0);
}
