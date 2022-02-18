/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:42:46 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/18 19:22:19 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"
#include "libftprintf.h"
#include "get_next_line.h"

void	ft_free_split(char **split_output)
{
	int	i;

	while (split_output[i])
	{
		free(split_output[i]);
		i++;
	}
	//free(split_output);
}

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

void	ft_init_fdf_map(t_fdf_map *map)
{
	map->y_max = 0;
}

void	ft_fdf_parse(char *str, t_fdf_map *map)
{
	char	**split_output;
	size_t		i;
	size_t	current_line;

	i = 0;
	current_line = map->y_max;
	ft_printf("current_line = %d\n", current_line);
	split_output = ft_split(str, ' ');
	map->x_max = ft_realloc(map->x_max, ((sizeof(int) * current_line)), 
			((sizeof(int) * (current_line + 1))));
	ft_printf("current_line = %u", current_line);
	map->x_max[current_line] = ft_array_size(split_output);
	map->z[current_line] = malloc(sizeof(*map->z) * map->x_max[current_line]);
	ft_printf("x_max = %d\n", map->x_max[current_line]);
	while (i < map->x_max[current_line])
	{
		map->z[current_line][i] = ft_atoi(split_output[i]);
		free(split_output[i]);
		ft_printf("%d ", map->z[current_line][i]);
		i++;
	}
	ft_putstr("\n");
	free(split_output);
}

int	ft_fdf_open_map(char *file, t_fdf_env *env)
{
	int			fd;
	char		*str;
	t_fdf_map	map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	//ft_init_fdf_map(&map);
	map.y_max = 0;
	env->map = &map;
	while (1)
	{
		str = get_next_line(fd);
		ft_fdf_parse(str, &map);
		ft_printf("%s", str);
		if (str == 0)
			break ;
		map.y_max++;
		free(str);
	}
	get_next_line(GNL_FLUSH);
	ft_printf("y_max == %d\n", map.y_max);
	close(fd);
	return (0);
}
