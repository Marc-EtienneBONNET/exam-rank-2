/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:08:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/28 17:14:57 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *remains, char *buffer)
{
	char			*array;
	unsigned int	size;
	int				i;
	int				j;

	if (!remains && !buffer)
		return (NULL);
	size = ft_strlen(remains) + ft_strlen(buffer);
	if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (remains && remains[i])
		array[j++] = remains[i++];
	i = 0;
	while (buffer[i])
		array[j++] = buffer[i++];
	array[size] = '\0';
	free((void *)remains);
	return (array);
}

char	*push_line(char *remains)
{
	int		i;
	char	*array;

	i = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i++] != '\n');
	if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (remains[++i] && remains[i] != '\n')
		array[i] = remains[i];
	array[i] = '\0';
	return (array);
}

char	*cut_next_line(char *remains)
{
	int		i;
	int		j;
	char	*array;

	i = 0;
	j = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i++] != '\n');
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains)- i + 1))))
		return (NULL);
	while (remains[i])
		array[j++] = remains[i++];
	array[j] = '\0';
	free(remains);
	return (array);
}

int	ft_check_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

char *get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*remains = NULL;
	static int			count = 1;
	char		*line;

	if (count == 0)
		return (NULL);
	buffer[0]='\0';
	count = 1;
	while (ft_check_nl(buffer) != 1 && count != 0)
	{
		if ((count = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (NULL);
		buffer[count] = '\0';
		remains = ft_strjoin(remains, buffer);
	}
	line = push_line(remains);
	remains = cut_next_line(remains);
	return (line);
}
