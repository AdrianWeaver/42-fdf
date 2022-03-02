/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:42:46 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/02 15:26:55 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"
#include "libftprintf.h"
#include "get_next_line.h"

/* sets up the map, use of malloc could have been avoided here			*/

t_fdf_map	*ft_init_fdf_map(t_fdf_env *env)
{
	t_fdf_map	*map;

	map = malloc(sizeof(*map) * 1);
	if (map == 0)
		return (0);
	env->map = map;
	map->y_max = 0;
	return (map);
}

/* frees the gnl right after it is used to memory is
 * not kept hostage for no reasons after the use						*/

t_fdf_str	*ft_getnext_gnl_and_free(t_fdf_str *gnl)
{
	free(gnl->str);
	return (gnl->next);
}

/* reads the string given as input by gnl, returns an int in the form
 * of an int** as such int[nb_of_lines][number_of_column] = value_z 	*/

void	ft_fdf_parse(t_fdf_str *gnl, t_fdf_map *map)
{
	char	**split_output;
	int		current_line;
	int		current_line_size;
	int		i;

	current_line = 0;
	map->z = malloc(sizeof(int *) * map->y_max);
	map->x_max = malloc(sizeof(int *) * map->y_max);
	while (gnl != 0)
	{
		i = -1;
		split_output = ft_split(gnl->str, ' ');
		current_line_size = ft_array_size(split_output);
		map->x_max[current_line] = current_line_size;
		map->z[current_line] = malloc(sizeof(int *) * current_line_size);
		while (++i < current_line_size)
		{
			map->z[current_line][i] = ft_atoi(split_output[i]);
			free(split_output[i]);
		}
		free(split_output);
		current_line++;
		gnl = ft_getnext_gnl_and_free(gnl);
	}
}

/* behaves as a mutant combining a lst_new function if prev is NULL
 * and a lst_addback otherwise by modifying the previous ->next			*/

t_fdf_str	*ft_fdf_lst_addback_new(t_fdf_env *env, char *str, t_fdf_str *prev)
{
	t_fdf_str	*ret;

	if (prev == env->img->img_str)
		prev = NULL;
	if (str == 0)
	{
		return (0);
	}
	ret = malloc(sizeof(*ret) * 1);
	if (ret == 0)
		return (0);
	if (!str)
		ret->str = NULL;
	else
		ret->str = str;
	ret->next = NULL;
	if (prev != 0)
		prev->next = ret;
	return (ret);
}

/* opens the map, check for errors and exit if encountered.
 * If the file is read, carries on with a gnl on it and send it to the
 * parse fonction														*/

int	ft_fdf_open_map(char *file, t_fdf_env *env)
{
	int			fd;
	t_fdf_map	*map;
	t_fdf_str	*gnl;
	t_fdf_str	*gnl_start;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit (-1);
	map = ft_init_fdf_map(env);
	gnl = env->img->img_str;
	gnl_start = NULL;
	while (gnl)
	{
		gnl = ft_fdf_lst_addback_new(env, get_next_line(fd), gnl);
		if (gnl_start == NULL && gnl != env->mlx_id)
			gnl_start = gnl;
		if (gnl != 0 && gnl->str != NULL)
			map->y_max++;
	}
	get_next_line(GNL_FLUSH);
	if (gnl_start == 0)
		ft_nuke_empty(env);
	ft_fdf_parse(gnl_start, map);
	ft_free_str(gnl_start);
	return (close(fd));
}
