/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:10:31 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/01 16:30:24 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	if (mlx == 0)
		return (-1);
	mlx_window = mlx_new_window(mlx, 500, 500, "my fancy mlx window");
	mlx_loop(mlx);
}
