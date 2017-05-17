/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:42:18 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/28 12:47:46 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_addr(size_t n, char *base, size_t *i)
{
	if (n >= 16)
		print_addr(n / 16, base, i);
	my_pc(base[(int)(n % 16)], 1);
	(*i)++;
}

size_t	print_pointer(t_spec *spec, va_list *args)
{
	size_t	i;
	void	*p;
	size_t	paddr;
	size_t	size;

	is_width_prec_in_args(spec, args);
	p = va_arg(*args, void *);
	paddr = (size_t)p;
	size = calc_size(paddr, 16);
	if ((i = 2) && !spec->flags.minus && spec->width > size - 2)
		((spec->flags.plus || spec->flags.space) && spec->width > size) ?
		(i += my_pc(' ', spec->width - size)) :
		(i += my_pc(' ', spec->width - size - 2));
	my_putstr("0x", 2);
	(size < spec->precision) ? (i += my_pc('0', spec->precision - size)) : 0;
	if (!(spec->is_precision && spec->precision == 0 && p == 0))
		print_addr(paddr, "0123456789abcdef", &i);
	if (spec->flags.minus && spec->width > size - 2)
		((spec->flags.plus || spec->flags.space) && spec->width > size) ?
		(i += my_pc(' ', spec->width - size)) :
		(i += my_pc(' ', spec->width - size - 2));
	return (i);
}
