/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:27:56 by leoniechen        #+#    #+#             */
/*   Updated: 2024/03/26 15:21:22 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	hex_to_dec(char *s)
{
	int	i;
	int	dec;
	int	digit;

	i = 0;
	dec = 0;
	digit = 0;
	if ((s[i] == '0' && s[i + 1] == 'x') || (s[i] == '0' && s[i + 1] == 'X'))
		i += 2;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			digit = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			digit = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			digit = s[i] - 'A' + 10;
		else
			return (-1);
		dec = dec * 16 + digit;
		i++;
	}
	return (dec);
}
