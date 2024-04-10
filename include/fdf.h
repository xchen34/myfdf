/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:39:32 by leochen           #+#    #+#             */
/*   Updated: 2024/04/09 17:54:39 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../include/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../printf/ft_printf.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define M_PI 3.14159265358979323846

typedef struct s_color
{
	int			color1;
	int			color2;
	int			changed_color1;
	int			changed_color2;
}				t_color;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_img;

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
	int			x2d;
	int			y2d;
}				t_point;

typedef struct s_matrix
{
	t_point		**point;
	int			width;
	int			height;
	int			z_max;
	int			z_min;
}				t_matrix;

typedef struct s_param
{
	float		alpha;
	float		beta;
	float		theta;
	double		scale;
	double		elevation;
	int			x_offset;
	int			y_offset;
	t_color		color;
	int			color_update_flag;
	int			isometric;
	int			top;
	int			conic;

}				t_param;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;
	t_matrix	matrix;
	t_param		param;
}				t_data;

typedef struct s_bresenham
{
	int			xdir;
	int			ydir;
}				t_bresenham;

typedef struct s_current_point
{
	int			x2d;
	int			y2d;
}				t_current_point;

typedef struct s_rotate
{
	int			rotate_x;
	int			rotate_y;
	int			rotate_z;
}				t_rotate;

typedef struct s_conic
{
	float		standard_parallel;
	float		central_meridian;
}				t_conic;

/*init data*/
int				init_all(t_data **data_ptr);

/*error.c*/
void			error_free_data(t_data *data);
void			error_free_data_tpoint(t_data *data, int allocated_height);
void			open_error(void);

/*parse_fdf_map*/
void			parse_one_line(char *line, t_data *data, int i);
void			set_matrix(t_data *data, int width, int height);
void			set_params(t_data *data);
void			parse_fdf_map(char *file_path, t_data *data);

/*parse util*/
void			parse_point(char *pt, t_data *data, int y, int x);
int				count_height(char *file_path, t_data *data);
int				count_width(char *file_path, t_data *data);
double			calculate_param_scale(t_data *data);
double			calculate_param_elevation(t_data *data);
int				hex_to_dec(char *s);
void			find_max_min_z(t_data *data);

/*draw map*/
int				draw_map(t_data *data);
void			set_background_color(t_data *data, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			perform_transform(t_data *data, int j, int i);
void			set_2d_cordinates(t_data *data);
float			degree_to_radian(int angle);
void			draw_line(t_data *data, int x, int y, int dir);
void			draw_projection(t_data *data);
void			bresenham_algo(t_data *data, t_point *pt1, t_point *pt2,
					t_bresenham *bresenham);

/*COLOR*/
int				create_rgb(int r, int g, int b);
void			set_point_color(t_data *data, t_point *p1);
int				set_line_color(t_point p1, t_point p2, t_point p);
void			set_endpoint_colors(t_data *data, t_point *p1, t_point *p2);
int				interpolate_color(int colorStart, int colorEnd, float ratio);

/*EXIT*/
int				close_window(t_data *data);
int				handle_key_press(int keycode, t_data *data);

/*BONUS*/
void			perform_translation(int keycode, t_data *data);
void			perform_rotation(int keycode, t_data *data);
void			perform_zoom(int keysym, t_data *data);
void			perform_elevation(int keysym, t_data *data);
void			perform_color(int keysym, t_data *data);
void			another_projection(int keysym, t_data *data);
void			perspective_projection(t_data *data, int j, int i);
int				perform_movement(int keycode, t_data *data);
void			perform_conic_projection(t_data *data, int j, int i,
					t_conic params);
void			perform_top(t_data *data, int j, int i);

#endif
