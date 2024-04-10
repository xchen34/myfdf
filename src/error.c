/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:48 by leochen           #+#    #+#             */
/*   Updated: 2024/04/05 17:07:24 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	error_free_data(t_data *data)
{
	free(data);
	exit(1);
}

void	error_free_data_tpoint(t_data *data, int allocated_height)
{
	while (allocated_height >= 0)
	{
		free(data->matrix.point[allocated_height]);
		allocated_height--;
	}
	free(data->matrix.point);
	free(data);
	exit(1);
}

void	open_error(void)
{
	perror("open error. please make sure there is only one valide file path!\n");
	exit(1);
}
