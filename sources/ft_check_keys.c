/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:11:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/18 08:34:10 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libftprintf.h"

int	ft_check_keys(int keycode, t_fdf_env *env)
{
	ft_printf("reached ft_check\n");
	if (keycode == KEY_ESC)
	{
		ft_nuke_program(env);
	}
	return (0);
}
