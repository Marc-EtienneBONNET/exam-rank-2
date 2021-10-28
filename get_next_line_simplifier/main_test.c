/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:28:36 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/28 17:11:43 by mbonnet          ###   ########.fr       */
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

	fd = open("test_3.txt",O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("(%s)\n", line);
		free(line);
	}
	close(fd);
}
