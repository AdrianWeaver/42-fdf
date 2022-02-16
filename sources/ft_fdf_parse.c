/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:42:46 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/16 22:26:49 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"
#include "libftprintf.h"
#include "get_next_line.h"

//void	ft_init_fdf_map(t_fdf_map *map)
//{
//}
	
//t_fdf_map	*ft_fdf_parse(int fd)
//{
	//t_fdf_map	map;
	//
	//ft_init_fdf_map(&map);
//
//}

int	ft_fdf_open_map(char *file)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	ft_printf("%s\n", str);
	free(str);
	//do
	//{
		//str = get_next_line(fd);
		//ft_printf("%s\n", str);
		//free(str);
	//} while (str);
	get_next_line(GNL_FLUSH);
	close(fd);
	return (0);
	//return (ft_fdf_parse(fd));
}
