/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 23:15:57 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 00:59:54 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

void	adjust_input(t_input *input, int board[SIZE][SIZE], t_pos *pos,
			int value)
{
	board[pos->row][pos->col] = value;
	input->horizontal[pos->row][value] = 0;
	input->vertical[pos->col][value] = 0;
}

void	return_input(t_input *input, int board[SIZE][SIZE], t_pos *pos,
			int value)
{
	input->horizontal[pos->row][value] = 1;
	input->vertical[pos->col][value] = 1;
	board[pos->row][pos->col] = 0;
}

void	go_next_grid(t_pos *pos)
{
	pos->col++;
	if (pos->col == SIZE)
	{
		pos->col = 0;
		pos->row++;
	}
}

void	restore_grid(t_pos *pos)
{
	pos->col--;
	if (pos->col == -1)
	{
		pos->col = SIZE - 1;
		pos->row--;
	}
}
