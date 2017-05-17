/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 10:34:56 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/15 15:16:18 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_bool	validate_piece(t_filler *n, t_cord *mine, t_bool is_x)
{
	int		x;
	int		y;
	t_bool	i;

	y = -1;
	i = FALSE;
	if ((n->p_row + mine->y > n->m_row) || (n->p_col + mine->x > n->m_col))
		return (FALSE);
	while (++y < n->p_row)
	{
		x = -1;
		while (++x < n->p_col)
		{
			if (n->piece[y][x] == '*')
			{
				if (n->map[mine->y + y][mine->x + x] == ((is_x) ? 'X' : 'O'))
					i++;
				if (n->map[mine->y + y][mine->x + x] == ((is_x) ? 'O' : 'X'))
					return (FALSE);
				if (n->map[mine->y + y][mine->x + x] == ((is_x) ? 'x' : 'o'))
					return (FALSE);
			}
		}
	}
	return ((i == TRUE) ? TRUE : FALSE);
}

static void		change_cord(t_filler *node, t_cord *change)
{
	if (change->x + 1 == node->m_col)
	{
		change->y++;
		change->x = 0;
	}
	else
		change->x++;
}

static void		change_min_dist(t_filler *node, t_cord *mine, int *min, int t)
{
	(*min) = t;
	node->x = mine->x;
	node->y = mine->y;
}

void			filler(t_filler *node, t_bool is_x)
{
	t_cord	mine;
	t_cord	enemy;
	int		tmp;
	int		min_dist;

	min_dist = 2147483647;
	ft_bzero(&mine, sizeof(t_cord));
	while ((mine.y < node->m_row - node->p_row + 1) && (mine.x <= node->m_col))
	{
		if (validate_piece(node, &mine, is_x))
		{
			ft_bzero(&enemy, sizeof(t_cord));
			while ((enemy.y < node->m_row) && (enemy.x < node->m_col))
			{
				if (node->map[enemy.y][enemy.x] == ((is_x) ? 'O' : 'X'))
					if ((tmp = ft_power(enemy.x - mine.x, 2) +
						ft_power(enemy.y - mine.y, 2)) < min_dist)
						change_min_dist(node, &mine, &min_dist, tmp);
				change_cord(node, &enemy);
			}
		}
		change_cord(node, &mine);
	}
}

void			free_node(t_filler *node)
{
	int i;

	i = -1;
	while (++i < node->m_row)
		free(node->map[i]);
	i = -1;
	while (++i < node->p_row)
		free(node->piece[i]);
	ft_bzero(node, sizeof(t_filler));
}
