/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:53:50 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/27 16:44:47 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_empty_struct(t_spec *spec)
{
	spec->flags.hash = FALSE;
	spec->flags.zero = FALSE;
	spec->flags.minus = FALSE;
	spec->flags.plus = FALSE;
	spec->flags.space = FALSE;
	spec->width_in_args = FALSE;
	spec->prec_in_args = FALSE;
	spec->length = default_len;
	spec->spec = DEFAULT_SPEC;
	spec->width = 0;
	spec->is_precision = FALSE;
	spec->precision = 0;
}

int		save_flags_2struct(t_spec *spec, const char *format)
{
	int	i;

	i = -1;
	while (format[++i] == '+' || format[i] == '-' || format[i] == ' ' ||
			format[i] == '#' || format[i] == '0')
	{
		if (format[i] == '#')
			spec->flags.hash = TRUE;
		else if (format[i] == '0')
			spec->flags.zero = TRUE;
		else if (format[i] == '-')
			spec->flags.minus = TRUE;
		else if (format[i] == '+')
			spec->flags.plus = TRUE;
		else if (format[i] == ' ')
			spec->flags.space = TRUE;
	}
	return (i);
}

int		save_width_prec_2struct(t_spec *spec, const char *format, int j)
{
	if (format[j] >= '0' && format[j] <= '9')
		spec->width = ft_atoi(format + j);
	while (format[j] >= '0' && format[j] <= '9')
		j++;
	if (format[j] == '*')
		spec->width_in_args = TRUE;
	(format[j] == '*') ? ++j : j;
	if (format[j] == '.')
		spec->is_precision = TRUE;
	(format[j] == '.') ? ++j : j;
	if (format[j] == '*' && spec->is_precision)
		spec->prec_in_args = TRUE;
	else
		spec->precision = ft_atoi(format + j);
	while (format[j] >= '0' && format[j] <= '9')
		j++;
	return (j);
}

int		save_len_2struct(t_spec *spec, const char *format, int j)
{
	if (format[j] == 'h' && format[j + 1] == 'h')
	{
		spec->length = hh;
		j += 2;
	}
	else if (format[j] == 'l' && format[j + 1] == 'l')
	{
		spec->length = ll;
		j += 2;
	}
	else if (format[j] == 'l' || format[j] == 'h' ||
			format[j] == 'j' || format[j] == 'z')
	{
		if (format[j] == 'l')
			spec->length = l;
		else if (format[j] == 'h')
			spec->length = h;
		else if (format[j] == 'z')
			spec->length = z;
		else if (format[j] == 'j')
			spec->length = 6;
		j++;
	}
	return (j);
}

void	save_spec_2struct(t_spec *spec, const char *format, int sl)
{
	if (format[sl] == 'd' || format[sl] == 'i' || format[sl] == 'D')
		spec->spec = DECIMAL;
	else if (format[sl] == 's' || format[sl] == 'S')
		spec->spec = STRING;
	else if (format[sl] == 'o' || format[sl] == 'O')
		spec->spec = OCTAL;
	else if (format[sl] == 'x')
		spec->spec = HEX_LOW;
	else if (format[sl] == 'X')
		spec->spec = HEX_UP;
	else if (format[sl] == 'p')
		spec->spec = POINTER;
	else if (format[sl] == 'u' || format[sl] == 'U')
		spec->spec = UNS_DEC;
	else if (format[sl] == 'c' || format[sl] == 'C')
		spec->spec = CHAR;
	else if (format[sl] == 'b')
		spec->spec = BINARY;
	else if (format[sl] == '%')
		spec->spec = PERCENT;
	if (format[sl] == 'D' || format[sl] == 'O' || format[sl] == 'U' ||
		format[sl] == 'S' || format[sl] == 'D' || format[sl] == 'C')
		spec->length = l;
}
