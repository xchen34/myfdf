/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils22.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:40:24 by leochen           #+#    #+#             */
/*   Updated: 2024/04/05 16:51:58 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

// 斜率绝对值小于1
static void	bresenham_direction_low(t_data *data, t_point *pt1, t_point *pt2,
	t_bresenham bresenham)
{
	int		error_accum;
	int		dy;
	int		dx;
	t_point	tmp;

	tmp = *pt1;
	dx = ft_abs(pt2->x2d - pt1->x2d);
	dy = ft_abs(pt2->y2d - pt1->y2d);
	error_accum = 2 * dy - dx;
	set_endpoint_colors(data, pt1, pt2);
	while (1)
	{
		my_mlx_pixel_put(data, tmp.x2d, tmp.y2d, set_line_color(*pt1, *pt2,
				tmp));
		if (tmp.x2d == pt2->x2d && tmp.y2d == pt2->y2d)
			break ;
		if (error_accum >= 0)
		{
			tmp.y2d += bresenham.ydir;
			error_accum -= dx * 2;
		}
		error_accum += 2 * dy;
		tmp.x2d += bresenham.xdir;
	}
}

// 斜率绝对值大于1
static void	bresenham_direction_high(t_data *data, t_point *pt1, t_point *pt2,
		t_bresenham bresenham)
{
	int		error_accum;
	int		dy;
	int		dx;
	t_point	tmp;

	tmp = *pt1;
	dx = ft_abs(pt2->x2d - pt1->x2d);
	dy = ft_abs(pt2->y2d - pt1->y2d);
	error_accum = 2 * dx - dy;
	set_endpoint_colors(data, pt1, pt2);
	while (1)
	{
		my_mlx_pixel_put(data, tmp.x2d, tmp.y2d, set_line_color(*pt1, *pt2,
				tmp));
		if (tmp.x2d == pt2->x2d && tmp.y2d == pt2->y2d)
			break ;
		if (error_accum >= 0)
		{
			tmp.x2d += bresenham.xdir;
			error_accum -= dy * 2;
		}
		error_accum += 2 * dx;
		tmp.y2d += bresenham.ydir;
	}
}

void	bresenham_algo(t_data *data, t_point *pt1, t_point *pt2,
	t_bresenham *bresenham)
{
	int	dx;
	int	dy;

	dx = ft_abs(pt2->x2d - pt1->x2d);
	dy = ft_abs(pt2->y2d - pt1->y2d);
	if (pt2->x2d < pt1->x2d)
		bresenham->xdir = -1;
	else
		bresenham->xdir = 1;
	if (pt2->y2d < pt1->y2d)
		bresenham->ydir = -1;
	else
		bresenham->ydir = 1;
	if (dx > dy)
	{
		bresenham_direction_low(data, pt1, pt2, *bresenham);
	}
	else
	{
		bresenham_direction_high(data, pt1, pt2, *bresenham);
	}
}
