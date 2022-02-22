/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:42:46 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/22 11:44:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"
#include "libftprintf.h"
#include "get_next_line.h"

int	ft_array_size(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

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

/* The purpose of this code is to keep an idea in place to try to 
 * free the gnl on the go, when they are no longer needed.
 * the following code is a prototype of what it should look like in a near future
 * the line gnl = ft_getnext_gnl_and_free should obviously be added in the
 * function ft_fdf_parse
 * */

//t_fdf_str	*ft_getnext_gnl_and_free(t_fdf_str *gnl)
//{
	//t_fdf_str	*next;
//
	//next = gnl->next;
	//free(gnl);
	//return (next);
//}

void	ft_fdf_parse(t_fdf_str *gnl, t_fdf_map *map)
{
	char	**split_output;
	int		current_line;
	int		current_line_size;
	int		i;

	current_line = 0;
	map->z = malloc(sizeof(int *) * map->y_max);
	map->x_max = malloc(sizeof(int *) * map->y_max);
	while (gnl-> str != 0)
	{
		i = 0;
		split_output = ft_split(gnl->str, ' ');
		current_line_size = ft_array_size(split_output);
		map->x_max[current_line] = current_line_size;
		map->z[current_line] = malloc(sizeof(int *) * current_line_size);
		while (i < current_line_size)
		{
			map->z[current_line][i] = ft_atoi(split_output[i]);
			free(split_output[i]);
			i++;
		}
		free(split_output);
		current_line++;
		gnl = gnl->next;
	}
}

t_fdf_str	*ft_fdf_lst_addback_new(char *str, t_fdf_str *prev)
{
	t_fdf_str	*ret;

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

int	ft_fdf_open_map(char *file, t_fdf_env *env)
{
	int			fd;
	t_fdf_map	*map;
	t_fdf_str	*gnl;
	t_fdf_str	*gnl_start;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	map = ft_init_fdf_map(env);
	gnl = ft_fdf_lst_addback_new(get_next_line(fd), NULL);
	gnl_start = gnl;
	map->y_max++;
	while (1)
	{
		gnl = ft_fdf_lst_addback_new(get_next_line(fd), gnl);
		if (gnl->str == NULL)
			break ;
		map->y_max++;
	}
	get_next_line(GNL_FLUSH);
	gnl = gnl_start;
	ft_fdf_parse(gnl, map);
	ft_free_str(gnl);
	close(fd);
	return (0);
}
