/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:42:14 by leochen           #+#    #+#             */
/*   Updated: 2024/04/08 19:56:04 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"

int	ft_printf(const char *format, ...);
int	print_c(char c);
int	print_d(int nb);
int	print_p(void *address);
int	print_s(char *s);
int	print_u(unsigned int nb);
int	print_x(unsigned int n, int uppercase);

#endif 
