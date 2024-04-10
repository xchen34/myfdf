/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:32:41 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 20:50:33 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	set_2d_cordinates_utile(t_data *data, t_conic *params)
{
	(*params).standard_parallel = 1;
	(*params).central_meridian = 1;
	(*params).standard_parallel = data->matrix.height / 2;
	(*params).central_meridian = data->matrix.width / 2;
}

void	set_2d_cordinates(t_data *data)
{
	int		i;
	int		j;
	t_conic	params;

	i = 0;
	j = 0;
	set_2d_cordinates_utile(data, &params);
	while (i < data->matrix.height)
	{
		j = 0;
		while (j < data->matrix.width)
		{
			if (data->param.isometric == 1 && data->param.top == 0
				&& data->param.conic == 0)
				perform_transform(data, j, i);
			else if (data->param.isometric == 0 && data->param.top == 0
				&& data->param.conic == 1)
				perform_conic_projection(data, j, i, params);
			else if (data->param.isometric == 0 && data->param.top == 1
				&& data->param.conic == 0)
				perform_top(data, j, i);
			j++;
		}
		i++;
	}
}

float	degree_to_radian(int angle)
{
	return (angle * (M_PI / 180.0));
}

static void	transform_iso2d(t_data *data, int j, int i, t_rotate rotate)
{
	data->matrix.point[i][j].x2d = (rotate.rotate_x - rotate.rotate_y)
		* cos(degree_to_radian(30));
	data->matrix.point[i][j].y2d = (rotate.rotate_x + rotate.rotate_y)
		* sin(degree_to_radian(30)) - rotate.rotate_z;
	data->matrix.point[i][j].x2d += data->param.x_offset;
	data->matrix.point[i][j].y2d += data->param.y_offset;
}

void	perform_transform(t_data *data, int j, int i)
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
	transform_iso2d(data, j, i, rotate);
}
