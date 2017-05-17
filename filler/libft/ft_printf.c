/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:53:51 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/23 13:54:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_specifier(t_spec *spec, va_list *args)
{
	size_t printed_count;

	printed_count = 0;
	if (spec->spec == STRING)
		printed_count = print_string(spec, args);
	else if (spec->spec == POINTER)
		printed_count = print_pointer(spec, args);
	else if (spec->spec == DECIMAL)
		printed_count = print_decimal(spec, args);
	else if (spec->spec == OCTAL)
		printed_count = print_octal(spec, args);
	else if (spec->spec == UNS_DEC)
		printed_count = print_udecimal(spec, args);
	else if (spec->spec == HEX_LOW)
		printed_count = print_hex_low(spec, args);
	else if (spec->spec == HEX_UP)
		printed_count = print_hex_up(spec, args);
	else if (spec->spec == CHAR)
		printed_count = print_char(spec, args);
	else if (spec->spec == BINARY)
		printed_count = print_binary(spec, args);
	else if (spec->spec == PERCENT)
		printed_count = print_percent(spec, args);
	return (printed_count);
}

static size_t	spec_struct_init(va_list *args, const char *format,
								int spec_len)
{
	size_t	printed;
	t_spec	*spec;
	int		j;

	if ((spec = (t_spec *)malloc(sizeof(t_spec))) == NULL)
		return (FALSE);
	init_empty_struct(spec);
	j = save_flags_2struct(spec, format);
	j = save_width_prec_2struct(spec, format, j);
	j = save_len_2struct(spec, format, j);
	save_spec_2struct(spec, format, spec_len - 1);
	printed = print_specifier(spec, args);
	free(spec);
	spec = NULL;
	return (printed);
}

static void		finish_printf(char **tmp, size_t *printed)
{
	if (**tmp == '%')
		while (**tmp == '%' || **tmp == 'h' || **tmp == ' ' ||
				**tmp == 'j' || **tmp == 'l' || **tmp == 'z')
			(*tmp)++;
	else
	{
		(*printed)++;
		write(1, (*tmp)++, 1);
	}
}

int				ft_printf(const char *format, ...)
{
	va_list		args;
	size_t		printed;
	int			spec_len;
	int			i;
	char		*tmp;

	if (!format)
		return (-1);
	tmp = (char *)format;
	va_start(args, format);
	printed = 0;
	while (*tmp)
	{
		(*tmp == '{') ? (tmp = check_color(&tmp)) : 0;
		if (*tmp == '%' && (spec_len = is_correct_spec(tmp)) > 0)
		{
			i = spec_struct_init(&args, tmp + 1, spec_len);
			(i > 0 && (printed += i)) ? (tmp += spec_len + 1)
			: (tmp += spec_len + 1);
		}
		else
			finish_printf(&tmp, &printed);
	}
	va_end(args);
	return (printed);
}
