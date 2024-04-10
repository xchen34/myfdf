/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:51:53 by leochen           #+#    #+#             */
/*   Updated: 2024/04/10 14:10:06 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	count_height(char *file_path, t_data *data)
{
	int		count;
	int		fd;
	char	*line;

	if (!file_path)
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_free_data(data);
	line = get_next_line(fd);
	count = 0;
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("height=%d\n", count);
	close(fd);
	return (count);
}

static int	count_width_util(char **tmp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp[count])
	{
		count++;
	}
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (count);
}

int	count_width(char *file_path, t_data *data)
{
	char	*line;
	char	**tmp;
	int		count;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_free_data(data);
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		tmp = ft_split(line, ' ');
		if (!tmp)
		{
			free(line);
			error_free_data(data);
		}
		count = count_width_util(tmp);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("width=%d\n", count);
	close(fd);
	return (count);
}

double	calculate_param_scale(t_data *data)
{
	int		max_size;
	float	scale;

	if (data->matrix.width >= data->matrix.height)
		max_size = data->matrix.width;
	else
		max_size = data->matrix.height;
	if (max_size == 0)
		return (0);
	scale = ((double)1920 / (double)(2 * max_size));
	ft_printf("first scale=%d\n", (int)scale);
	return (scale);
}

double	calculate_param_elevation(t_data *data)
{
	float	elevation;

	elevation = (double)(1080 / 5);
	if (data->matrix.z_max == data->matrix.z_min)
		return (0);
	elevation /= (double)(data->matrix.z_max - data->matrix.z_min);
	ft_printf("first evation=%d\n", (int)elevation);
	return (elevation);
}
