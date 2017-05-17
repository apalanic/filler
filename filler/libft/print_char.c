/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:48:31 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/30 14:03:19 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_percent(t_spec *spec, va_list *args)
{
	size_t	printed;

	printed = 1;
	is_width_prec_in_args(spec, args);
	if (spec->flags.minus)
		my_pc('%', 1);
	if (spec->width > 1)
	{
		if (spec->flags.zero && !spec->flags.minus)
			printed += my_pc('0', spec->width - 1);
		else
			printed += my_pc(' ', spec->width - 1);
	}
	if (!spec->flags.minus)
		my_pc('%', 1);
	return (printed);
}

int			print_char(t_spec *spec, va_list *args)
{
	size_t			printed;
	unsigned char	c;

	printed = 0;
	is_width_prec_in_args(spec, args);
	c = (unsigned char)va_arg(*args, int);
	if (spec->flags.minus)
		my_pc(c, 1);
	if (spec->width > 1)
		printed += my_pc(' ', spec->width - 1);
	if (!spec->flags.minus)
		my_pc(c, 1);
	printed++;
	return (printed);
}
