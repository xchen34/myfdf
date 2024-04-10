/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:23:25 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 20:53:43 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	perform_conic_projection(t_data *data, int j, int i, t_conic params)
{
	float	rho;
	float	theta;
	float	x_;
	float	y_;

	rho = fabs(params.standard_parallel - data->matrix.point[i][j].y)
		* data->param.scale;
	theta = (data->matrix.point[i][j].x - params.central_meridian)
		* cos(degree_to_radian(params.standard_parallel));
	x_ = rho * sin(theta) + data->param.x_offset;
	y_ = rho * cos(theta) + data->param.y_offset;
	data->matrix.point[i][j].x2d = x_;
	data->matrix.point[i][j].y2d = y_;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
