/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:06:13 by leochen           #+#    #+#             */
/*   Updated: 2024/04/06 18:23:49 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*read_and_add(int fd, char *stock)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stock, '\n') && bytes_read > 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		bytes_read = (int)read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stock = add_to_stock(stock, buf);
		free(buf);
	}
	return (stock);
}

char	*extract_from_stock(char *stock)
{
	char	*line;
	int		i;

	i = 0;
	if (stock[0] == '\0')
		return (NULL);
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_extracted_stock(char *stock)
{
	int		i;
	int		j;
	char	*new_stock;

	i = 0;
	j = 0;
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	if (stock[i] == '\0')
	{
		free(stock);
		return (NULL);
	}
	new_stock = (char *)malloc(sizeof(char) * ft_strlen(stock) - i);
	if (new_stock == NULL)
		return (NULL);
	i = i + 1;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	free(stock);
	return (new_stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = read_and_add(fd, stock);
	if (stock == NULL)
		return (NULL);
	line = extract_from_stock(stock);
	stock = clean_extracted_stock(stock);
	return (line);
}
