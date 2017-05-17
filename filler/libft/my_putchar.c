/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 11:04:52 by apalanic          #+#    #+#             */
/*   Updated: 2016/11/25 19:09:20 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		my_pc(char c, int size)
{
	int	i;

	i = 0;
	if (size <= 0)
		return (0);
	while (i++ < size)
		write(1, &c, 1);
	return (--i);
}

int		my_putstr(const char *s, int n)
{
	int	i;

	i = 0;
	if (s == NULL || n <= 0)
		return (0);
	while (i < n)
		write(1, &s[i++], 1);
	return (i);
}
