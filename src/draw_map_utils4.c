/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:00:28 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 20:26:29 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	set_line_color(t_point p1, t_point p2, t_point p)
{
	double	ratio;
	double	total_distance;
	double	point_distance;

	total_distance = sqrt(pow(p2.x2d - p1.x2d, 2) + pow(p2.y2d - p1.y2d, 2));
	point_distance = sqrt(pow(p.x2d - p1.x2d, 2) + pow(p.y2d - p1.y2d, 2));
	ratio = point_distance / total_distance;
	return (interpolate_color(p1.color, p2.color, ratio));
}

void	set_point_color(t_data *data, t_point *p)
{
	float	scale;

	if (p->color != -1 && data->param.color_update_flag == 1)
	{
		return ;
	}
	scale = (p->z - data->matrix.z_min) / (float)(data->matrix.z_max
			- data->matrix.z_min);
	p->color = interpolate_color(data->param.color.color1,
			data->param.color.color2,
			scale);
}

void	set_endpoint_colors(t_data *data, t_point *p1, t_point *p2)
{
	set_point_color(data, p1);
	set_point_color(data, p2);
}

static void	do_top2d(t_data *data, int j, int i, t_rotate rotate)
{
	data->matrix.point[i][j].x2d = rotate.rotate_x;
	data->matrix.point[i][j].y2d = rotate.rotate_y;
	data->matrix.point[i][j].x2d += data->param.x_offset;
	data->matrix.point[i][j].y2d += data->param.y_offset;
}

void	perform_top(t_data *data, int j, int i)
{
	int			temp_x;
	int			temp_y;
	int			temp_z;
	t_rotate	rotate;

	temp_x = data->matrix.point[i][j].x * data->param.scale;
	temp_y = data->matrix.point[i][j].y * data->param.scale;
	temp_z = data->matrix.point[i][j].z * data->param.elevation;
	rotate.rotate_y = temp_y * cos(data->param.alpha) + temp_z
		* sin(data->param.alpha);
	rotate.rotate_z = -temp_y * sin(data->param.alpha) + temp_z
		* cos(data->param.alpha);
	temp_z = rotate.rotate_z;
	rotate.rotate_x = temp_x * cos(data->param.beta) + temp_z
		* sin(data->param.beta);
	rotate.rotate_z = -temp_x * sin(data->param.beta) + temp_z
		* cos(data->param.beta);
	temp_x = rotate.rotate_x;
	temp_y = rotate.rotate_y;
	rotate.rotate_x = temp_x * cos(data->param.theta) - temp_y
		* sin(data->param.theta);
	rotate.rotate_y = temp_x * sin(data->param.theta) + temp_y
		* cos(data->param.theta);
	do_top2d(data, j, i, rotate);
}
