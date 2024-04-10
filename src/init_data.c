/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:40:11 by leochen           #+#    #+#             */
/*   Updated: 2024/04/09 17:57:30 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../mlx_linux/mlx.h"

static int	init_img(t_data *data, void *mlx_ptr)
{
	data->img.mlx_img = NULL;
	data->img.addr = NULL;
	data->img.bits_per_pixel = 0;
	data->img.line_length = 0;
	data->img.endian = 0;
	data->img.mlx_img = mlx_new_image(mlx_ptr, 1920, 1080);
	if (!data->img.mlx_img)
		return (-1);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	if (!data->img.addr)
		return (-1);
	return (1);
}

static int	init_matrix(t_data *data)
{
	data->matrix.point = NULL;
	data->matrix.width = 0;
	data->matrix.height = 0;
	data->matrix.z_max = -2147483648;
	data->matrix.z_min = 2147483647;
	return (1);
}

static int	init_param(t_data *data)
{
	data->param.alpha = 0;
	data->param.beta = 0;
	data->param.theta = 0;
	data->param.elevation = 0;
	data->param.scale = 0;
	data->param.x_offset = 1;
	data->param.y_offset = -1;
	data->param.color.color1 = 0;
	data->param.color.color2 = 0;
	data->param.color.changed_color1 = 0;
	data->param.color.changed_color2 = 0;
	data->param.color_update_flag = 1;
	data->param.isometric = 1;
	data->param.top = 0;
	data->param.conic = 0;
	return (1);
}

int	init_all(t_data **data_ptr)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_free_data(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_free_data(data);
	data->mlx_win = mlx_new_window(data->mlx_ptr, 1920, 1080, "fdf map");
	if (!data->mlx_win)
		error_free_data(data);
	if (init_img(data, data->mlx_ptr) != 1)
		error_free_data(data);
	if (init_matrix(data) != 1)
		error_free_data(data);
	if (init_param(data) != 1)
		error_free_data(data);
	*data_ptr = data;
	return (1);
}
