/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:40:11 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 19:58:29 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	ft_printf("start from here 1\n");
	data = NULL;
	if (argc != 2 || open(argv[1], O_RDONLY) < 0)
		open_error();
	init_all(&data);
	ft_printf("init done\n");
	parse_fdf_map(argv[1], data);
	ft_printf("parse done\n");
	mlx_loop_hook(data->mlx_ptr, &draw_map, data);
	mlx_key_hook(data->mlx_win, &handle_key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	close_window(t_data *data)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_display(data->mlx_ptr);
	i = 0;
	while (i < data->matrix.height && data->matrix.point[i])
	{
		free(data->matrix.point[i]);
		data->matrix.point[i] = NULL;
		i++;
	}
	free(data->matrix.point);
	data->matrix.point = NULL;
	free(data->mlx_ptr);
	if (data)
		free(data);
	exit(0);
}

int	press_esc(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_window(data);
	}
	return (0);
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_window(data);
	}
	else
	{
		perform_movement(keycode, data);
	}
	return (0);
}
