/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:53:51 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/23 13:54:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_binary(t_spec *spec, va_list *args)
{
	size_t				i;
	unsigned long long	o;
	size_t				size;

	is_width_prec_in_args(spec, args);
	o = cast_flag_len_uns(va_arg(*args, unsigned long long), spec);
	size = calc_size(o, 2);
	i = size;
	if (spec->is_precision && spec->precision > size && (i = spec->precision))
		size = spec->precision;
	if (!spec->flags.minus && spec->width > size)
	{
		(spec->flags.hash) ? (i += my_pc(' ', spec->width - size - 2))
		: (i += my_pc(' ', spec->width - size));
		(spec->flags.hash) ? (i += my_putstr("0b", 2)) : 0;
		print_uns(o, size, "01");
	}
	else
	{
		(spec->flags.hash) ? (i += my_putstr("0b", 2)) : 0;
		print_uns(o, size, "01");
		(spec->flags.hash) ? (i += my_pc(' ', spec->width - size - 2))
		: (i += my_pc(' ', spec->width - size));
	}
	return (i);
}
