/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:42:57 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 23:05:11 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	validate_input(int **board, int rules[SIDES][SIZE], int row)
{
	if (!check_left(board, rules, row)
		|| !check_right(board, rules, row)
		|| !check_vertical(board, rules, row))
		return (0);
	return (1);
}

int	solve(int **board, int rules[SIDES][SIZE], int row, int **solution)
{
	int	i;

	i = 0;
	while (i < ALL_SOLN)
	{
		board[row] = solution[i];
		if (validate_input(board, rules, row))
		{
			if (row == SIZE - 1)
				return (print_board(board));
			if (solve(board, rules, row + 1, solution))
				return (1);
		}
		i++;
	}
	return (0);
}

// how do i prevent rechecking of the lines left and right
// check left + right
// check duplicate and check min-max