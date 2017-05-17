/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:03:00 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/30 10:42:54 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_octal(t_spec *spec, va_list *args)
{
	size_t				i;
	unsigned long long	o;
	size_t				size;

	is_width_prec_in_args(spec, args);
	o = cast_flag_len_uns(va_arg(*args, unsigned long long), spec);
	size = calc_size(o, 8);
	(spec->flags.hash && o > 0) ? (size++) : size;
	if (spec->precision > size || (spec->width > size && spec->flags.zero &&
		!spec->flags.minus))
		(spec->is_precision) ? (size = spec->precision)
		: (size = spec->width);
	if ((i = size) && spec->is_precision && spec->precision == 0 && o == 0)
		(spec->flags.hash) ? (i = my_pc('0', 1))
		: (i = my_pc(' ', spec->width));
	else if (!spec->flags.minus && spec->width > size &&
			(i += my_pc(' ', spec->width - size)))
		print_uns(o, size, "01234567");
	else
	{
		print_uns(o, size, "01234567");
		i += my_pc(' ', spec->width - size);
	}
	return (i);
}
