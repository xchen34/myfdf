/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:55:37 by leochen           #+#    #+#             */
/*   Updated: 2023/11/30 18:58:19 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digit(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static void	put_x(unsigned int n, int uppercase)
{
	static char	base1[] = "0123456789abcdef";
	static char	base2[] = "0123456789ABCDEF";

	if (uppercase == 0)
	{
		if (n >= 16)
		{
			put_x(n / 16, uppercase);
			ft_putchar_fd(base1[n % 16], 1);
		}
		else
			ft_putchar_fd(base1[n % 16], 1);
	}
	else
	{
		if (n >= 16)
		{
			put_x(n / 16, uppercase);
			ft_putchar_fd(base2[n % 16], 1);
		}
		else
			ft_putchar_fd(base2[n % 16], 1);
	}
}

int	print_x(unsigned int n, int uppercase)
{
	put_x(n, uppercase);
	return (count_digit(n));
}
