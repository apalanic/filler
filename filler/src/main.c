/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 09:50:02 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/15 10:31:29 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

static void	save_map_size(t_filler *node)
{
	int		i;
	char	*tmp;

	i = 8;
	if (get_next_line(0, &tmp) <= 0)
		return ;
	node->m_row = ft_atoi(tmp + i);
	while (*(tmp + i) >= '0' && *(tmp + i) <= '9')
		i++;
	node->m_col = ft_atoi(tmp + i);
	free(tmp);
}

static void	save_piece_size(t_filler *node)
{
	int		i;
	char	*tmp;

	i = 6;
	if (get_next_line(0, &tmp) <= 0)
		return ;
	node->p_row = ft_atoi(tmp + i);
	while (*(tmp + i) >= '0' && *(tmp + i) <= '9')
		i++;
	node->p_col = ft_atoi(tmp + i);
	free(tmp);
}

static void	save_map(t_filler *node)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((node->map = (char **)malloc(sizeof(char *) * node->m_row)) == NULL)
		return ;
	while (i < node->m_row)
	{
		get_next_line(0, &tmp);
		if (tmp[0] >= '0' && tmp[0] <= '9')
			node->map[i++] = ft_strdup(&tmp[4]);
		free(tmp);
	}
}

static void	save_piece(t_filler *node)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((node->piece = (char **)malloc(sizeof(char *) * node->p_row)) == NULL)
		return ;
	while (i < node->p_row)
	{
		get_next_line(0, &tmp);
		if (tmp[0] >= '.' || tmp[0] <= '*')
			node->piece[i++] = ft_strdup(tmp);
		free(tmp);
	}
}

int			main(void)
{
	t_filler	node;
	char		*tmp;
	t_bool		is_x;

	is_x = FALSE;
	ft_bzero(&node, sizeof(t_filler));
	get_next_line(0, &tmp);
	if (ft_strstr(tmp, "p2"))
		is_x = TRUE;
	free(tmp);
	while (TRUE)
	{
		save_map_size(&node);
		save_map(&node);
		save_piece_size(&node);
		save_piece(&node);
		filler(&node, is_x);
		ft_printf("%d %d\n", node.y, node.x);
		free_node(&node);
	}
	return (0);
}
