/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:26:55 by leoniechen        #+#    #+#             */
/*   Updated: 2024/04/09 18:47:26 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	perform_translation(int keysym, t_data *data)
{
	if (keysym == XK_Left && data->param.x_offset > 0)
		data->param.x_offset -= 10;
	if (keysym == XK_Right && data->param.x_offset < 1920)
		data->param.x_offset += 10;
	if (keysym == XK_Up && data->param.y_offset > 0)
		data->param.y_offset -= 10;
	if (keysym == XK_Down && data->param.y_offset < 1080)
		data->param.y_offset += 10;
}

void	perform_rotation(int keysym, t_data *data)
{
	if (keysym == XK_s)
		data->param.alpha += 0.05;
	if (keysym == XK_w)
		data->param.alpha -= 0.05;
	if (keysym == XK_d)
		data->param.beta += 0.05;
	if (keysym == XK_a)
		data->param.beta -= 0.05;
	if (keysym == XK_e)
		data->param.theta += 0.05;
	if (keysym == XK_q)
		data->param.theta -= 0.05;
}

void	perform_zoom(int keysym, t_data *data)
{
	float	old_scale;
	float	old_elevation;
	float	scale_ratio;

	old_scale = data->param.scale;
	old_elevation = data->param.elevation;
	if (keysym == XK_minus)
	{
		data->param.scale -= 2;
		if (data->param.scale <= 0)
		{
			data->param.scale = old_scale * 0.9;
			data->param.elevation = old_elevation * 0.5;
		}
		else
		{
			scale_ratio = data->param.scale / old_scale;
			data->param.elevation *= scale_ratio;
		}
	}
	if (keysym == XK_equal)
	{
		data->param.scale += 0.4;
		data->param.elevation *= 1 + 0.4 / data->param.scale;
	}
}

void	perform_elevation(int keysym, t_data *data)
{
	if (keysym == XK_1)
		data->param.elevation *= 1.1;
	if (keysym == XK_0)
		data->param.elevation *= 0.9;
}

void	perform_color(int keysym, t_data *data)
{
	if (keysym == XK_space)
	{
		ft_printf("before change color1=%d\n", data->param.color.color1);
		if (data->param.color.color1 != data->param.color.changed_color1)
		{
			data->param.color.color1 = data->param.color.changed_color1;
			data->param.color_update_flag = 0;
		}
		else
		{
			data->param.color.color1 = create_rgb(59, 239, 251);
			data->param.color_update_flag = 0;
		}
		ft_printf("after change color1=%d\n", data->param.color.color1);
	}
}
