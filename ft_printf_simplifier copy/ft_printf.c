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

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
int TOTALE = 0;

void	ft_write(char c)
{
	TOTALE += 1;
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = -1;

	while (str[++i])
		ft_write(str[i]);
}

int		check_num(int number)
{
	unsigned int num;
	int			len;

	len = 0;
	if (number == 0)
		return (1);
	else if (number < 0)
	{
		len++;
		num = number * -1;
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

int	check_long(unsigned int number)
{
	int len;

	len = 0;
	if (number == 0)
		return (1);
	while(number > 0)
	{
		number /= 16;
		len++;
	}
	return (len);
}

char *get_num(int number, int size)
{
	unsigned int num;
	char *nb;

	if (!(nb = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	nb[size] = '\0';
	if (number == 0)
	{
		nb[0] = '0';
		return (nb);
	}
	else if (number < 0)
		num = number * -1;
	else 
		num = number;
	while (--size > 0)
	{
		nb[size] = num % 10 + '0';
		num /= 10;
	}
	if (number < 0)
		nb[size] = '-';
	else 
		nb[size] = num % 10 + '0';
	return (nb);
}

char *get_long(unsigned int number, int size)
{
	char *nb;
	char *hex = "0123456789abcdef";

	if (!(nb = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	nb[size] = '\0';
	if (number == 0)
	{
		nb[0] = '0';
		return (nb);
	}
	while (--size > 0)
	{
		nb[size] = hex[number % 16];
		number /= 16;
	}
	nb[size] = hex[number % 16];
	return (nb);
}

void	ft_print_num(va_list value)
{
	int num;
	char *str_num;

	num = va_arg(value, int);
	str_num = get_num(num, check_num(num));
	ft_putstr(str_num);
}

void	ft_print_xxx(va_list value)
{
	unsigned int num;
	char *str_num;

	num = va_arg(value, unsigned int);
	str_num = get_long(num, check_long(num));
	ft_putstr(str_num);
}

void ft_print_str(va_list value)
{
	char *str;

	str = va_arg(value, char *);
	if (!str)
		ft_putstr("(null)");
	else 
		ft_putstr(str);
}

void	ft_choose_flags(char c, va_list value)
{
	if (c == 'd')
		ft_print_num(value);
	if (c== 's')
		ft_print_str(value);
	if (c == 'x')
		ft_print_xxx(value);
}

int	ft_printf(char *str, ...)
{
	int i;
	va_list value;

	i = 0;
	TOTALE = 0;
	va_start(value, str);
	while (str[i])
	{
		if (str[i] == '%')
			ft_choose_flags(str[++i], value);
		else 
			ft_write(str[i]);
		i++;
	}
	va_end(value);
	return (TOTALE);
}