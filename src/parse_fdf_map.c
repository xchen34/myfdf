/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:40:11 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 19:58:48 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	parse_one_line(char *line, t_data *data, int i)
{
	int		j;
	char	**one_line_pts;

	j = 0;
	one_line_pts = ft_split(line, ' ');
	if (!one_line_pts)
		error_free_data_tpoint(data, data->matrix.height);
	while (one_line_pts[j] != NULL)
	{
		parse_point(one_line_pts[j], data, i, j);
		j++;
	}
	j = 0;
	while (one_line_pts[j])
	{
		free(one_line_pts[j]);
		j++;
	}
	free(one_line_pts);
}

static void	init_2dxy(t_data *data, int i, int j)
{
	data->matrix.point[i][j].x2d = -1;
	data->matrix.point[i][j].y2d = -1;
}

void	set_matrix(t_data *data, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->matrix.point = (t_point **)malloc(sizeof(t_point *) * height);
	if (!data->matrix.point)
		error_free_data(data);
	while (i < height)
	{
		data->matrix.point[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!data->matrix.point[i])
			error_free_data_tpoint(data, i);
		j = 0;
		while (j < width)
		{
			data->matrix.point[i][j].x = (j) - ((width) - 1) / 2;
			data->matrix.point[i][j].y = (i) - ((height) - 1) / 2;
			init_2dxy(data, i, j);
			j++;
		}
		i++;
	}
	data->matrix.width = width;
	data->matrix.height = height;
}

void	parse_fdf_map(char *file_path, t_data *data)
{
	int		fd;
	int		y;
	char	*line;
	int		height;

	height = count_height(file_path, data);
	set_matrix(data, count_width(file_path, data), height);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_free_data_tpoint(data, data->matrix.height);
	else
		ft_printf("open success\n");
	line = NULL;
	y = 0;
	line = get_next_line(fd);
	while (y < height)
	{
		parse_one_line(line, data, y);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	set_params(data);
	close(fd);
}
