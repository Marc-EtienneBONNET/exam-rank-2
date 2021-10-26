/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:08:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/26 11:44:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"
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
	while (remains[i] && remains[i++] != '\n');
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains)- i + 1))))
		return (NULL);
	while (remains[++i])
	{
		array[j++] = remains[i];
	}
	array[j] = '\0';
	free(remains);
	return (array);
}

int	ft_check_nl(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remains = NULL;
	static int	fin = 0;
	int			count;
	char		*line;

	count = 1;
	buffer = NULL;
	if (remains == NULL)
		if (!(buffer=malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (NULL);
	if (fin == 1)
		return (NULL);
	while (!ft_check_nl(buffer) && count != 0)
	{
		if ((count = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count] = '\0';
		remains = ft_strjoin(remains, buffer);
	}
	line = push_line(remains);
	remains = cut_next_line(remains);
	if (count == 0)
		fin = 1;
	free(buffer);
	return (line);
}
