/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 13:13:08 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/19 16:50:48 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_letters(const char *format, int i)
{
	while (format[i] == 'h' || format[i] == 'l' || format[i] == 'j'
		|| format[i] == 'z')
		i++;
	while (format[i] == '#' || format[i] == '0' || format[i] == '-' ||
			format[i] == '+' || format[i] == ' ')
		i++;
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '.' && ++i)
	{
		if (format[i] == '*')
			i++;
		while (format[i] >= '0' && format[i] <= '9')
			i++;
	}
	if (format[i] == 's' || format[i] == 'S' || format[i] == 'p' ||
		format[i] == 'd' || format[i] == 'D' || format[i] == 'i' ||
		format[i] == 'o' || format[i] == 'O' || format[i] == 'u' ||
		format[i] == 'U' || format[i] == 'x' || format[i] == 'X' ||
		format[i] == 'c' || format[i] == 'C' || format[i] == '%' ||
		format[i] == 'b')
		return (i);
	return (FALSE);
}

int		is_correct_spec(const char *format)
{
	int i;

	i = 0;
	if (format[i] == '%')
		i++;
	while (format[i] == '#' || format[i] == '0' || format[i] == '-' ||
			format[i] == '+' || format[i] == ' ')
		i++;
	if (format[i] == '*')
		i++;
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '.' && ++i)
	{
		if (format[i] == '*')
			i++;
		else
			while (format[i] >= '0' && format[i] <= '9')
				i++;
	}
	return (check_letters(format, i));
}
