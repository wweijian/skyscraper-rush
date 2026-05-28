/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjhoe <wjhoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:42:57 by weijian           #+#    #+#             */
/*   Updated: 2026/05/28 13:49:48 by wjhoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static void init_board(t_board board)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SIZE)
	{
		while (j < SIZE)
		{
			board[i][j] = 0;
			j++;
		}
		i++;
	}
}

static int validate_input(t_condition *condition, t_pos *pos, t_board *board, t_input *input)
{
	if (!check_top(condition->top, pos, board, input)
		|| !check_left(condition->left, pos, board, input)
		|| !check_right(condition->right, pos, board, input)
		|| !check_bottom(condition->bottom, pos, board, input))
		return (0);
	(*board)[pos->row][pos->col] = input->value;
	return (1);
}

static void	adjust_input(t_input *input, int new_value, int not_new)
{
	if (not_new)
	{
		input->horizontal[input->value] = 1;
		input->vertical[input->value] = 1;

	}
	input->value = new_value;
	input->horizontal[new_value] = 0;
	input->vertical[new_value] = 0;
}

int solve(t_condition *condition, t_pos *pos, t_input *input)
{
	int			i;
	static int	board[SIZE][SIZE];
	static long	count = 0;

	i = 0;
	count++;
	printf("row:%d\tcol:%d\tcount: %ld\n", pos->row, pos->col, count);
	init_board(board);
	while (i < SIZE)
	{
		if (input->horizontal[i] == 1 && input->vertical[i] == 1 && validate_input(condition, pos, &board, input))
		{
			adjust_input(input, i + 1, i);
			if (pos->col == SIZE - 1 && pos->row == SIZE - 1)
				return print_board(board);
			if (pos->col == SIZE - 1)
			{
				pos->row++;
				pos->col = 0;
			}
			else
				pos->col++;
			if (solve(condition, pos, input) == 1)
				return print_board(board);
		}
		i++;
	}
	return (0);
}
