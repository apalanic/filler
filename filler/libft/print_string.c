/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:42:18 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/28 12:47:46 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	finish_string(t_spec *spec, size_t len, size_t *i, char *s)
{
	if (!spec->flags.minus && !spec->is_precision)
		(*i) += my_putstr(s, len);
	else if (!spec->flags.minus && spec->is_precision)
		(len > spec->precision) ? ((*i) += my_putstr(s, spec->precision)) :
		((*i) += my_putstr(s, len));
}

size_t		print_string(t_spec *spec, va_list *args)
{
	size_t	i;
	char	*s;
	size_t	len;

	is_width_prec_in_args(spec, args);
	i = 0;
	if ((s = va_arg(*args, char *)) == NULL)
		return (i += my_putstr("(null)", 6));
	len = ft_strlen(s);
	if (spec->flags.minus && !spec->is_precision)
		i += my_putstr(s, len);
	else if (spec->flags.minus && spec->is_precision && len > 0)
		(len > spec->precision) ? (i += my_putstr(s, spec->precision)) :
		(i += my_putstr(s, len));
	if (!spec->is_precision && spec->width > len)
		i += my_pc(' ', spec->width - len);
	else if (spec->is_precision && spec->width > spec->precision && len == 0)
		i += my_pc(' ', spec->width);
	else if (spec->is_precision)
		(len > spec->precision)
		? (i += my_pc(' ', spec->width - spec->precision))
		: (i += my_pc(' ', spec->width - len));
	finish_string(spec, len, &i, s);
	return (i);
}
