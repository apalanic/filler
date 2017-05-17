/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 09:45:04 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/15 09:49:41 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft.h"
# include <limits.h>
# define TRUE		1
# define FALSE		0

typedef int			t_bool;

typedef struct		s_cord
{
	int				y;
	int				x;
}					t_cord;

typedef struct		s_filler
{
	char			**map;
	char			**piece;
	int				m_row;
	int				m_col;
	int				p_row;
	int				p_col;
	int				x;
	int				y;
}					t_filler;

void				filler(t_filler *node, t_bool is_x);
void				free_node(t_filler *node);

#endif
