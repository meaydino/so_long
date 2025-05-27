/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:49:36 by meaydino          #+#    #+#             */
/*   Updated: 2025/05/26 15:03:34 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*so_strdup(char *str, int len)
{
	char	*array;
	int		count;

	if (!str || !len)
		return (NULL);
	count = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	while (++count < len)
		array[count] = str[count];
	array[count] = '\0';
	return (array);
}
static int	have_n(char *temp)
{
	int	i;

	if (!temp)
		return (0);
	i = -1;
	while (temp[++i])
		if (temp[i] == 10)
			return (1);
	return (0);
}

static char	*print_line(char **temp)
{
	int		n_pos;
	char	*return_line;
	char	*str;

	if (!*temp)
		return (NULL);
	str = *temp;
	n_pos = 0;
	while (str[n_pos] && str[n_pos] != 10)
		n_pos++;
	if (str[n_pos] == 10)
		n_pos++;
	return_line = so_strdup(str, n_pos);
	*temp = so_strdup(str + n_pos, ft_strlen(str + n_pos));
	if (str)
		free(str);
	str = NULL;
	return (return_line);
}
char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(temp), temp = NULL, NULL);
	if (have_n(temp))
		return (print_line(&temp));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp), free(buffer), temp = NULL, NULL);
		buffer[bytes_read] = 0;
		temp = ft_strjoin(temp, buffer);
		if (have_n(temp))
			break ;
	}
	if (buffer)
		free(buffer);
	return (buffer = NULL, print_line(&temp));
}
