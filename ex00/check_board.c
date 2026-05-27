/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 22:12:47 by weijian           #+#    #+#             */
/*   Updated: 2026/05/28 00:19:41 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	check_left(int left[SIZE][SIZE], t_pos *pos, t_board *board, t_input *input)
{
	int	i;
	int	tallest;
	int	max;
	int min;

	i = 0;
	tallest = 0;
	min = 0;
	while (i <= pos->col)
	{
		min += check_visibility((*board)[pos->row][i], &tallest);
		i++;
	}
	i = tallest;
	max = min;
	while (i < SIZE)
	{
		if (input->horizontal[i] == 1)
			max++;
		i++;
	}
	min += max > min;
	return (left[pos->row][pos->col] <= max && left[pos->row][pos->col] >= min);
}

int	check_top(int top[SIZE][SIZE], t_pos *pos, t_board *board, t_input *input)
{
	int	i;
	int	tallest;
	int	max;
	int min;

	i = 0;
	tallest = 0;
	min = 0;
	while (i <= pos->row)
	{
		min += check_visibility((*board)[i][pos->col], &tallest);
		i++;
	}
	i = tallest;
	max = min;
	while (i < SIZE)
	{
		if (input->vertical[i] == 1)
			max++;
		i++;
	}
	min += max > min;
	return (top[pos->row][pos->col] <= max && top[pos->row][pos->col] >= min);
}

int	check_right(int right[SIZE][SIZE], t_pos *pos, t_board *board, t_input *input)
{
	int	i;
	int	tallest;
	int	max;
	int min;

	i = SIZE - 1;
	tallest = tallest_remainder(input->horizontal);
	max = 0;
	min = tallest != 0;
	while (i >= 0)
	{
		if (i > pos->col)
			max++;
		else if (check_visibility((*board)[pos->row][i], &tallest))
		{
			max++;
			min++;
		}
		i--;
	}
	return (right[pos->row][pos->col] <= max && right[pos->row][pos->col] >= min);
}

int	check_bottom(int bottom[SIZE][SIZE], t_pos *pos, t_board *board, t_input *input)
{
	int	i;
	int	tallest;
	int	max;
	int min;

	i = SIZE - 1;
	tallest = tallest_remainder(input->vertical);
	max = 0;
	min = tallest != 0;
	while (i >= 0)
	{
		if (i > pos->row)
			max++;
		else if (check_visibility((*board)[i][pos->col], &tallest))
		{
			max++;
			min++;
		}
		i--;
	}
	return (bottom[pos->row][pos->col] <= max && bottom[pos->row][pos->col] >= min);
}