/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:26:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/16 12:05:11 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_put_pixel_img(t_fdf_img *img, int x, int y, int colour)
{
	char	*dst_pixel;

	dst_pixel = img->img_ptr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst_pixel = colour;
}
