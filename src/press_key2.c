/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:00:21 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 18:30:34 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	another_projection(int keysym, t_data *data)
{
	data->param.alpha = 0;
	data->param.beta = 0;
	data->param.theta = 0;
	data->param.x_offset = 1920 / 2;
	data->param.y_offset = 1080 / 2;
	if (keysym == XK_i)
	{
		data->param.isometric = 1;
		data->param.top = 0;
		data->param.conic = 0;
	}
	if (keysym == XK_t)
	{
		data->param.isometric = 0;
		data->param.top = 1;
		data->param.conic = 0;
	}
	if (keysym == XK_c)
	{
		data->param.isometric = 0;
		data->param.top = 0;
		data->param.conic = 1;
	}
}

int	perform_movement(int keysym, t_data *data)
{
	if (keysym == XK_Up || keysym == XK_Down || keysym == XK_Left
		|| keysym == XK_Right)
		perform_translation(keysym, data);
	if (keysym == XK_a || keysym == XK_d || keysym == XK_w || keysym == XK_s
		|| keysym == XK_q || keysym == XK_e)
		perform_rotation(keysym, data);
	if (keysym == XK_minus || keysym == XK_equal)
		perform_zoom(keysym, data);
	if (keysym == XK_0 || keysym == XK_1)
		perform_elevation(keysym, data);
	if (keysym == XK_space)
		perform_color(keysym, data);
	if (keysym == XK_c || keysym == XK_i || keysym == XK_t)
		another_projection(keysym, data);
	draw_map(data);
	return (0);
}
