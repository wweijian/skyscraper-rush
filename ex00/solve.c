/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:42:57 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 00:59:39 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	validate_input(t_condition *condition, t_pos *pos,
							int (*board)[SIZE][SIZE], t_input *input)
{
	if (!check_top(condition->top, pos, board, input)
		|| !check_left(condition->left, pos, board, input)
		|| !check_right(condition->right, pos, board, input)
		|| !check_bottom(condition->bottom, pos, board, input))
		return (0);
	return (1);
}

int	solve(t_condition *condition, t_pos *pos, t_input *input)
{
	int			i;
	static int	board[SIZE][SIZE];

	i = 0;
	while (i < SIZE)
	{
		if (input->horizontal[pos->row][i] == 1
			&& input->vertical[pos->col][i] == 1)
		{
			adjust_input(input, board, pos, i);
			if (validate_input(condition, pos, &board, input))
			{
				if (pos->col == SIZE - 1 && pos->row == SIZE - 1)
					return (print_board(board));
				go_next_grid(pos);
				if (solve(condition, pos, input) == 1)
					return (1);
				restore_grid(pos);
			}
			return_input(input, board, pos, i);
		}
		i++;
	}
	return (0);
}
