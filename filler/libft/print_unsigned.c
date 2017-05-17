/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:53:51 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/23 13:54:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	cast_flag_len_uns(unsigned long long n, t_spec *spec)
{
	if (spec->length == hh)
		return ((unsigned char)n);
	else if (spec->length == h)
		return ((unsigned short)n);
	else if (spec->length == l)
		return ((unsigned long)n);
	else if (spec->length == ll)
		return ((unsigned long long)n);
	else if (spec->length == z)
		return ((size_t)n);
	else if (spec->length == j)
		return ((uintmax_t)n);
	return ((unsigned int)n);
}

void				print_uns(unsigned long long n, int precision, char *base)
{
	unsigned long long	base_size;
	int					n_size;

	n_size = 0;
	base_size = ft_strlen(base);
	if (base_size == 8)
		n_size = calc_size(n, 8);
	else if (base_size == 16)
		n_size = calc_size(n, 16);
	else if (base_size == 2)
		n_size = calc_size(n, 2);
	else if (base_size == 10)
		n_size = calc_size(n, 10);
	while (--precision >= n_size)
		my_pc('0', 1);
	if (n >= base_size)
		print_uns(n / base_size, 0, base);
	my_pc(base[(size_t)n % base_size], 1);
}

static void			finish_udecimal(t_spec *spec, size_t size, size_t *i,
									unsigned long long o)
{
	if (!spec->flags.minus && spec->width > size)
	{
		(spec->flags.zero) ? ((*i) += my_pc('0', spec->width - size)) :
		((*i) += my_pc(' ', spec->width - size));
		print_uns(o, size, "0123456789");
	}
	else
	{
		print_uns(o, size, "0123456789");
		(spec->flags.zero && !spec->flags.minus) ?
		((*i) += my_pc('0', spec->width - size))
		: ((*i) += my_pc(' ', spec->width - size));
	}
}

size_t				print_udecimal(t_spec *spec, va_list *args)
{
	size_t				i;
	unsigned long long	o;
	size_t				size;

	o = cast_flag_len_uns(va_arg(*args, unsigned long long), spec);
	size = calc_size(o, 10);
	i = size;
	if (spec->is_precision && spec->precision > size && (i = spec->precision))
		size = spec->precision;
	if (spec->is_precision && spec->precision == 0 && o == 0)
	{
		i = 0;
		(spec->width > size) ? i += my_pc(' ', spec->width - size + 1) : 0;
		(spec->flags.space && spec->width < size) ? i += my_pc(' ', 1) : 0;
		return (i);
	}
	finish_udecimal(spec, size, &i, o);
	return (i);
}
