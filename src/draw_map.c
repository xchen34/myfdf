/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:39:12 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 20:27:40 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	draw_map(t_data *data)
{
	ft_printf("enter draw map\n");
	if (data->mlx_win == NULL)
		return (0);
	set_background_color(data, create_rgb(0, 0, 0));
	draw_projection(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.mlx_img,
		0, 0);
	return (1);
}

void	set_background_color(t_data *data, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_line(t_data *data, int i, int j, int dir)
{
	t_point		*p1;
	t_point		*p2;
	t_bresenham	bresenham;

	p1 = &data->matrix.point[i][j];
	if (dir == 1 && j + 1 < data->matrix.width)
	{
		p2 = &data->matrix.point[i][j + 1];
	}
	else if (dir == 0 && i + 1 < data->matrix.height)
	{
		p2 = &data->matrix.point[i + 1][j];
	}
	else
	{
		return ;
	}
	bresenham_algo(data, p1, p2, &bresenham);
}

void	draw_projection(t_data *data)
{
	int	i;
	int	j;

	set_2d_cordinates(data);
	i = 0;
	while (i < data->matrix.height)
	{
		j = 0;
		while (j < data->matrix.width)
		{
			if (j + 1 != data->matrix.width)
				draw_line(data, i, j, 1);
			if (i + 1 != data->matrix.height)
				draw_line(data, i, j, 0);
			j++;
		}
		i++;
	}
}
