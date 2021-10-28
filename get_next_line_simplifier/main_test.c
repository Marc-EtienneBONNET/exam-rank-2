/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:28:36 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/26 11:32:40 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char	*line;
	int		fd;
	int x = 0;

	fd = open("test_2.txt",O_RDONLY);
	while ((line = get_next_line(fd)) != NULL && x < 3)
	{
		printf("(%s)\n", line);
		x++;
		free(line);
	}
	close(fd);
}
