/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:26:23 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 22:40:15 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/* probably the most important function of all, gets coords (x,y) and sets
 * the proper colour to the appropriate index on the image string so the
 * color can be displayed after as image								*/

void	ft_put_pixel_img(t_fdf_img *img, int x, int y, int colour)
{
	char	*dst_pixel;

	dst_pixel = img->img_str
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst_pixel = colour;
}
