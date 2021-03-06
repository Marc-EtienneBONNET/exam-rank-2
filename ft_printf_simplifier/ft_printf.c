/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:42:53 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/26 10:05:56 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int TOTALE = 0;

void	ft_write(char c)
{
	TOTALE++;
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i; 

	i = 0;
	while (str[i])
		ft_write(str[i++]);
}

int		check_num(int number)
{
	unsigned int size;
	unsigned int num;

	size = 0;
	if (number == 0)
		return (1);
	else if (number < 0)
	{
		size++;
		num = number * -1;
	}
	else 
		num = number;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

int check_long(unsigned int number)
{
	unsigned int size;

	size = 0;
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number /= 16;
		size++;
	}
	return (size);
}

char *get_num(int number, int size)
{
	unsigned int num;
	char *array;

	if (!(array = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	array[size] = '\0';
	if (number == 0)
	{
		array[0] = '0';
		return (array);
	}
	else if (number < 0)
		num = number * -1;
	else 
		num = number;
	while (--size > 0)
	{
		array[size] = num % 10 + '0';
		num /= 10;
	}
	if (number < 0)
		array[size] = '-';
	else 
		array[size] = num % 10 + '0';
	return (array);
}

char *get_long(unsigned int number, int size)
{
	char *array;
	char *hex = "0123456789abcdef";

	if (!(array = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	array[size] = '\0';
	if (number < 0)
	{
		array[0] = '0';
		return (array);
	}
	while (--size > 0)
	{
		array[size] = hex[number % 16];
		number /= 16;
	}
	array[size] = hex[number % 16];
	return (array);
}

void	print_num(va_list value)
{
	int number;
	char *str_num;

	number = va_arg(value, int);
	str_num = get_num(number, check_num(number));
	ft_putstr(str_num);
}

void	print_long(va_list value)
{
	unsigned int number;
	char *str_num;

	number = va_arg(value, unsigned int);
	str_num = get_long(number, check_long(number));
	ft_putstr(str_num);
}

void	print_str(va_list value)
{
	char *str;

	str = va_arg(value, char *);
	if (!str)
		ft_putstr("(null)");
	else 
		ft_putstr(str);
}

void	choose_flag(char c, va_list value)
{
	if (c == 'd')
		print_num(value);
	if (c == 'x')
		print_long(value);
	if (c == 's')
		print_str(value);
}

int ft_printf(char *str, ...)
{
	int i;
	va_list value;

	i = 0;
	TOTALE = 0;
	va_start(value, str);
	while (str[i])
	{
		if (str[i] == '%')
			choose_flag(str[++i], value);
		else 
			ft_write(str[i]);
		i++;
	}
	va_end(value);
	return (TOTALE);
}

