/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 13:13:08 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/19 16:50:48 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	calc_size(unsigned long long n, int base)
{
	size_t	size;

	size = 1;
	while (n / base > 0)
	{
		n /= base;
		size++;
	}
	return (size);
}

void	is_width_prec_in_args(t_spec *spec, va_list *args)
{
	int	tmp;

	if (spec->width_in_args)
	{
		tmp = va_arg(*args, int);
		if (tmp < 0)
		{
			spec->flags.minus = TRUE;
			tmp = -tmp;
		}
		spec->width = (size_t)tmp;
	}
	if (spec->is_precision && spec->prec_in_args)
	{
		tmp = va_arg(*args, int);
		if (tmp < 0)
			tmp = -tmp;
		spec->precision = (size_t)tmp;
	}
}
