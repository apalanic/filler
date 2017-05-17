/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:53:51 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/23 13:54:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*change_macro(char **format, char *color)
{
	char	*tmp;

	if ((tmp = (char *)malloc(ft_strlen(*format) + 5)) == NULL)
		return (NULL);
	ft_memcpy(tmp, color, 6);
	while (**format != '}')
		(*format)++;
	(*format)++;
	ft_memcpy(tmp + 5, (*format), ft_strlen(*format) + 1);
	return (tmp);
}

char		*check_color(char **format)
{
	char	*s;

	s = *format;
	if (!(ft_strncmp(s, "{red}", 5)))
		return (change_macro(format, RED));
	else if (!(ft_strncmp(s, "{green}", 7)))
		return (change_macro(format, GREEN));
	else if (!(ft_strncmp(s, "{yellow}", 8)))
		return (change_macro(format, YELLOW));
	else if (!(ft_strncmp(s, "{blue}", 6)))
		return (change_macro(format, BLUE));
	else if (!(ft_strncmp(s, "{magenta}", 9)))
		return (change_macro(format, MAGENTA));
	else if (!(ft_strncmp(s, "{cyan}", 6)))
		return (change_macro(format, CYAN));
	else if (!(ft_strncmp(s, "{white}", 7)))
		return (change_macro(format, WHITE));
	else if (!(ft_strncmp(s, "{eoc}", 5)))
		return (change_macro(format, EOC));
	else
		return (*format);
}
