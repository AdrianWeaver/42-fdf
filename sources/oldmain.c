/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:32:48 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/04 16:52:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (-1);
	fd = open(av[1]);
	if (fd == -1)
		return (-1);
	ft_fdf(fd);
	return (0);
}
