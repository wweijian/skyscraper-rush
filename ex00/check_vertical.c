/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 12:32:33 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 22:46:04 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	check_unique(int **board, int row, int appeared[SIZE][SIZE])
{
	int	col;
	int	j;

	col = 0;
	while (col < SIZE)
	{
		j = 0;
		while (j < row)
		{
			if (board[j][col] == board[row][col])
				return (0);
			appeared[col][board[j][col]] = 1;
			j++;
		}
		appeared[col][board[row][col]] = 1;
		col++;
	}
	return (1);
}

static int	check_top(int **board, int rules[SIDES][SIZE],
						int row, int appeared[SIZE][SIZE])
{
	int	i;
	int	col;
	int	min;
	int	max;
	int	tallest;

	col = 0;
	while (col < SIZE)
	{
		i = -1;
		min = 0;
		max = 0;
		tallest = -1;
		while (++i <= row)
			min += check_visibility(board[i][col], &tallest);
		max = min;
		min += tallest < tallest_remainder(appeared, col);
		i = tallest;
		while (++i < SIZE)
			max += appeared[col][i] == 0;
		if (rules[TOP][col] > max || rules[TOP][col] < min)
			return (0);
		col++;
	}
	return (1);
}

static int	check_bottom(int **board, int rules[SIDES][SIZE],
							int row, int appeared[SIZE][SIZE])
{
	int	i;
	int	col;
	int	max;
	int	min;
	int	tallest;

	col = -1;
	while (++col < SIZE)
	{
		i = row + 1;
		max = SIZE - row - 1;
		tallest = tallest_remainder(appeared, col);
		min = tallest != -1;
		while (--i >= 0)
		{
			if (check_visibility(board[i][col], &tallest))
			{
				min++;
				max++;
			}
		}
		if (rules[BOTTOM][col] > max || rules[BOTTOM][col] < min)
			return (0);
	}
	return (1);
}

int	check_vertical(int **board, int rules[SIDES][SIZE], int row)
{
	int	appeared[SIZE][SIZE];

	zero_appeared(appeared);
	return (check_unique(board, row, appeared)
		&& check_top(board, rules, row, appeared)
		&& check_bottom(board, rules, row, appeared));
}
