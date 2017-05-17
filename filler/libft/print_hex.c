/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:03:00 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/30 10:42:54 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hex_low_finish(t_spec *spec, size_t *i, size_t size,
							unsigned long long o)
{
	if (spec->flags.hash && o > 0 && spec->width == size && size == *i)
		my_putstr("0x", 2);
	else if (spec->flags.hash && o > 0)
		(*i) += my_putstr("0x", 2);
	if (spec->flags.hash)
		print_uns(o, size - 2, "0123456789abcdef");
	else
		print_uns(o, size, "0123456789abcdef");
	if (spec->flags.hash)
		(*i) += my_pc(' ', spec->width - size - 2);
	else
		(*i) += my_pc(' ', spec->width - size);
}

size_t		print_hex_low(t_spec *spec, va_list *args)
{
	size_t				i;
	unsigned long long	o;
	size_t				size;

	is_width_prec_in_args(spec, args);
	o = cast_flag_len_uns(va_arg(*args, unsigned long long), spec);
	size = calc_size(o, 16);
	if (spec->precision > size || (spec->width > size && spec->flags.zero &&
		!spec->flags.minus))
		(spec->is_precision) ? (size = spec->precision)
								: (size = spec->width);
	if (spec->is_precision && spec->precision == 0 && o == 0)
		(i = my_pc(' ', spec->width));
	else if ((i = size) && !spec->flags.minus && spec->width > size)
	{
		(spec->flags.hash) ? (i += my_pc(' ', spec->width - size - 2))
		: (i += my_pc(' ', spec->width - size));
		(spec->flags.hash && o > 0) ? (i += my_putstr("0x", 2)) : 0;
		print_uns(o, size, "0123456789abcdef");
	}
	else
		hex_low_finish(spec, &i, size, o);
	return (i);
}

static void	hex_up_finish(t_spec *spec, size_t *i, size_t size,
							unsigned long long o)
{
	if (spec->flags.hash && o > 0 && spec->width == size && size == *i)
		my_putstr("0X", 2);
	else if (spec->flags.hash && o > 0)
		(*i) += my_putstr("0X", 2);
	if (spec->flags.hash)
		print_uns(o, size - 2, "0123456789ABCDEF");
	else
		print_uns(o, size, "0123456789ABCDEF");
	if (spec->flags.hash)
		(*i) += my_pc(' ', spec->width - size - 2);
	else
		(*i) += my_pc(' ', spec->width - size);
}

size_t		print_hex_up(t_spec *spec, va_list *args)
{
	size_t				i;
	unsigned long long	o;
	size_t				size;

	is_width_prec_in_args(spec, args);
	o = cast_flag_len_uns(va_arg(*args, unsigned long long), spec);
	size = calc_size(o, 16);
	if (spec->precision > size || (spec->width > size && spec->flags.zero &&
		!spec->flags.minus))
		(spec->is_precision) ? (size = spec->precision)
							: (size = spec->width);
	if (spec->is_precision && spec->precision == 0 && o == 0)
		(i = my_pc(' ', spec->width));
	else if ((i = size) && !spec->flags.minus && spec->width > size)
	{
		(spec->flags.hash) ? (i += my_pc(' ', spec->width - size - 2))
		: (i += my_pc(' ', spec->width - size));
		(spec->flags.hash && o > 0) ? (i += my_putstr("0X", 2)) : 0;
		print_uns(o, size, "0123456789ABCDEF");
	}
	else
		hex_up_finish(spec, &i, size, o);
	return (i);
}
