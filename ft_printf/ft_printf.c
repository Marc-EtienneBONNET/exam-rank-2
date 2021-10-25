/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:42:53 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/25 18:04:19 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int TOTALE;

void	ft_write(char c)
{
	write(1, &c, 1);
	TOTALE++;
}

int	ft_putstr(char *str)
{
	int	x = -1;

	while (str[++x])
		ft_write(str[x]);
	return (x);
}

int	check_size(int number)
{
	unsigned int	num;
	int				len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		num = number * -1;
		len++;
	}
	else
		num = number;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	check_long(int number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	while (number > 0)
	{
		len++;
		number /= 16;
	}
	return (len);
}

char	*get_num(int number, int size)
{
	unsigned	num;
	char		*str;

	str = malloc(sizeof(char ) * (size + 1));
	str[size] = '\0';
	if (number == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (number < 0)
		num = number * -1;
	else
		num = number;
	while (--size > 0)
	{
		str[size] = (num % 10) + '0';
		num /= 10;
	}
	if (number < 0)
		str[size] = '-';
	else
		str[size] = (num % 10) + '0';
	return (str);
}

char	*get_long(unsigned int number)
{
	char	*str;
	int		size;
	char	*array_hex = "0123456789abcdef";

	size = check_long(number);
	str = malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	if (number == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (--size > 0)
	{
		str[size] = array_hex[number % 16];
		number /= 16;
	}
	if (size == 0)
		str[size] = array_hex[number % 16];
	return (str);
}

void	print_int(va_list value)
{
	int		number;
	char	*str;

	number = va_arg(value, int);
	str = get_num(number, check_size(number));
	ft_putstr(str);
	free(str);
}

void	print_xxx(va_list value)
{
	char			*str;

	str = get_long(va_arg(value, unsigned int));
	ft_putstr(str);
	free(str);
}

void	print_str(va_list value)
{
	char	*str;
	int		size;

	str = va_arg(value, char *);
	if (!str)
		str = "(null)";
	ft_putstr(str);
}

void	choose_balise(char c, va_list value)
{
	if (c == 'd')
		print_int(value);
	else if (c == 's')
		print_str(value);
	else if (c == 'x')
		print_xxx(value);
}

int	ft_printf(char *str, ...)
{
	va_list	value;
	int		i; 

	TOTALE = 0;
	i = 0;
	va_start(value, str);
	while (str[i])
	{
		if (str[i] == '%')
			choose_balise(str[++i], value);
		else
			ft_write(str[i]);
		i++;
	}
	va_end(value);
	return (TOTALE);
}
