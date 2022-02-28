/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:51:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 13:03:53 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

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
	t_fdf_str *save;
	while (gnl)
	{
		save = gnl;
		gnl = gnl->next;
		free(save);
	}
	return ;
	//t_fdf_str	*tmp;

	//while (gnl->str)
	//{
		//free(gnl->str);
		//tmp = gnl;
		//gnl = gnl->next;
		//free(tmp);
	//}
	//free(gnl);
}
