/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:42:34 by leoniechen        #+#    #+#             */
/*   Updated: 2024/04/10 17:06:42 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

static int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

static int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	interpolate_color(int color1, int color2, float ratio)
{
	int	r;
	int	g;
	int	b;

	ratio = fmax(0.0, fmin(ratio, 1.0));
	r = get_r(color1) + (int)((get_r(color2) - get_r(color1)) * ratio);
	g = get_g(color1) + (int)((get_g(color2) - get_g(color1)) * ratio);
	b = get_b(color1) + (int)((get_b(color2) - get_b(color1)) * ratio);
	return ((r << 16) | (g << 8) | b);
}
