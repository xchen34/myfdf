/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:49:42 by leochen           #+#    #+#             */
/*   Updated: 2024/04/09 14:44:55 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	parse_point(char *pt, t_data *data, int i, int j)
{
	int		z;
	int		color;
	char	**tmp;

	tmp = ft_split(pt, ',');
	if (tmp == NULL)
		error_free_data_tpoint(data, data->matrix.height);
	if (tmp[0])
	{
		z = ft_atoi(tmp[0]);
		data->matrix.point[i][j].z = z;
	}
	else
		error_free_data_tpoint(data, data->matrix.height);
	if (tmp[1])
	{
		color = hex_to_dec(tmp[1]);
		data->matrix.point[i][j].color = color;
	}
	else if (!tmp[1])
		data->matrix.point[i][j].color = -1;
	free_tmp(tmp);
}

void	set_params(t_data *data)
{
	data->param.alpha = 0;
	data->param.beta = 0;
	data->param.theta = 0;
	data->param.x_offset = 1920 / 2;
	data->param.y_offset = 1080 / 2;
	find_max_min_z(data);
	data->param.scale = calculate_param_scale(data);
	data->param.elevation = calculate_param_elevation(data);
	data->param.color.color1 = create_rgb(59, 239, 251);
	data->param.color.color2 = create_rgb(242, 245, 51);
	data->param.color.changed_color1 = create_rgb(30, 30, 30);
	data->param.color.changed_color2 = create_rgb(242, 245, 51);
}

void	find_max_min_z(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->matrix.height)
	{
		j = 0;
		while (j < data->matrix.width)
		{
			if (data->matrix.point[i][j].z > data->matrix.z_max)
				data->matrix.z_max = data->matrix.point[i][j].z;
			if (data->matrix.point[i][j].z < data->matrix.z_min)
				data->matrix.z_min = data->matrix.point[i][j].z;
			j++;
		}
		i++;
	}
}
