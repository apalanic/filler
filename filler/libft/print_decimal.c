/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:53:51 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/23 13:54:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	cast_flag_len_signed(long long n, t_spec *spec)
{
	if (spec->length == hh)
		return ((char)n);
	else if (spec->length == h)
		return ((short)n);
	else if (spec->length == l)
		return ((long)n);
	else if (spec->length == ll)
		return ((long long)n);
	else if (spec->length == z)
		return ((ssize_t)n);
	else if (spec->length == j)
		return ((intmax_t)n);
	return ((int)n);
}

static void	finish_decimal_2(t_spec *spec, size_t *i, size_t sz, long long d)
{
	if (d >= 0 && spec->flags.space && spec->width < sz
		&& !spec->flags.plus)
		(*i) += my_pc(' ', 1);
	if (spec->width > sz && !spec->flags.minus)
		(d < 0 || spec->flags.plus)
		? ((*i) += my_pc(' ', spec->width - sz - 1))
		: ((*i) += my_pc(' ', spec->width - sz));
	if (d < 0 || spec->flags.plus)
		(d < 0) ? ((*i) += my_pc('-', 1)) : ((*i) += my_pc('+', 1));
	(d < 0) ? (print_uns((-d), sz, "0123456789"))
	: (print_uns(d, sz, "0123456789"));
	if (spec->width > sz && spec->flags.minus)
		(d < 0 || spec->flags.plus)
		? ((*i) += my_pc(' ', spec->width - sz - 1))
		: ((*i) += my_pc(' ', spec->width - sz));
}

static void	finish_decimal_1(t_spec *spec, size_t *i, size_t sz, long long d)
{
	if (spec->is_precision && spec->precision == 0 && d == 0)
	{
		(*i) = 0;
		(spec->width > sz) ? (*i) += my_pc(' ', spec->width - sz + 1) : 0;
		(spec->flags.space && spec->width < sz) ? (*i) += my_pc(' ', 1) : 0;
	}
	else
	{
		if (d >= 0 && !spec->flags.minus && !spec->flags.plus)
		{
			if (d == 0 && spec->flags.zero && spec->width > 1
				&& !spec->is_precision)
			{
				sz--;
				(*i)--;
			}
			if (spec->flags.space && spec->width < sz)
				(*i) += my_pc(' ', 1);
			if (spec->width > sz)
				(*i) += my_pc(' ', spec->width - sz);
			print_uns(d, sz, "0123456789");
		}
		else
			finish_decimal_2(spec, i, sz, d);
	}
}

size_t		print_decimal(t_spec *spec, va_list *args)
{
	size_t		i;
	size_t		size;
	long long	d;

	is_width_prec_in_args(spec, args);
	d = cast_flag_len_signed(va_arg(*args, long long), spec);
	(d < 0) ? (size = calc_size(-(d), 10))
			: (size = calc_size(d, 10));
	if (spec->precision > size || (spec->width > size && spec->flags.zero
		&& !spec->flags.minus))
	{
		if (spec->is_precision)
			size = spec->precision;
		else
			(spec->flags.minus || spec->flags.plus || d < 0)
			? (size = spec->width - 1)
			: (size = spec->width);
	}
	i = size;
	finish_decimal_1(spec, &i, size, d);
	return (i);
}
