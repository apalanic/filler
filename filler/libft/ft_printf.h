/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:42:30 by apalanic          #+#    #+#             */
/*   Updated: 2017/01/28 12:41:21 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "libft.h"

# define FALSE		0
# define TRUE		1
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define EOC		"\x1B[00m"

/*
**	Define bool cos we not allow to use standart bool
*/

typedef int			t_bool;

/*
**	Define struct for flags #0-+ and space. '0' If a precision is given
**	with a numeric conversion (d, i, o, u, i, x, and X), the 0 flag is ignored
**	'-' A negative field width flag; the converted value is to be left adjusted
**	on the field boundary.  Except for n conversions, the converted value is
**	padded on the right with blanks, rather than on the left with blanks or
**	zeros.	A '-' overrides a '0' if both are given.
*/

typedef struct		s_flags
{
	t_bool			hash;
	t_bool			zero;
	t_bool			minus;
	t_bool			plus;
	t_bool			space;
}					t_flags;

/*
**	Define length flags. The following length modifiers are valid for the
**	d, i, n, o, u, x, or X conversion
*/

typedef enum		e_length
{
	default_len, hh, h, l, ll, z, j, len
}					t_length;

/*
**	Define specifiers S == ls, DUO == ldlulo,  i == d
*/

typedef enum		e_spec_letter
{
	DEFAULT_SPEC, STRING, POINTER, DECIMAL, OCTAL, UNS_DEC, HEX_LOW, HEX_UP,
	CHAR, BINARY, PERCENT
}					t_spec_letter;

/*
**	main struct for every specifier
*/

typedef struct		s_spec
{
	t_flags			flags;
	t_bool			width_in_args;
	t_bool			prec_in_args;
	t_length		length;
	t_spec_letter	spec;
	size_t			width;
	t_bool			is_precision;
	size_t			precision;

}					t_spec;

int					ft_atoi(const char *s);
int					ft_printf(const char *format, ...);
/*
**	Check if specifier is correct
*/
t_bool				is_correct_spec(const char *format);
/*
**	initialize struct to 0
*/
void				init_empty_struct(t_spec *spec);
/*
**	set t_bool TRUE to all flags
*/
int					save_flags_2struct(t_spec *spec, const char *format);
/*
**	save width and precision to struct if needed
*/
int					save_width_prec_2struct(t_spec *spec, const char *format,
											int j);
/*
**	save len 2 struct if needed
*/
int					save_len_2struct(t_spec *spec, const char *format, int j);
/*
**	save specifier ID in struct
*/
void				save_spec_2struct(t_spec *spec, const char *format,
										int sl);
/*
**	checks if width or precision is in args and save its nums to struct
*/
void				is_width_prec_in_args(t_spec *spec, va_list *args);
/*
**	calc size for base
*/
size_t				calc_size(unsigned long long n, int base);
/*
**	functions for print
*/
size_t				print_percent(t_spec *spec, va_list *args);
int					print_char(t_spec *spec, va_list *args);
size_t				print_string(t_spec *spec, va_list *args);
void				print_uns(unsigned long long n, int precision, char *base);
size_t				print_pointer(t_spec *spec, va_list *args);
size_t				print_octal(t_spec *spec, va_list *args);
size_t				print_hex_up(t_spec *spec, va_list *args);
size_t				print_hex_low(t_spec *spec, va_list *args);
size_t				print_binary(t_spec *spec, va_list *args);
size_t				print_udecimal(t_spec *spec, va_list *args);
size_t				print_decimal(t_spec *spec, va_list *args);
/*
**	my putchar and putstr with returned value of printed chars
*/
int					my_pc(char c, int size);
int					my_putstr(const char *s, int n);
/*
**	Cast flags hh, h, l, ll, j, z
*/
unsigned long long	cast_flag_len_uns(unsigned long long n, t_spec *spec);
long long			cast_flag_len_signed(long long n, t_spec *spec);
/*
**	Calculate size of number for print
*/
size_t				calc_size_signed(long long n, int base);
/*
**	For bonus color task
*/
char				*check_color(char **format);

#endif
