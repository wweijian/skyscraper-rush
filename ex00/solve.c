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
#include <stdlib.h>

#define LINES (SIZE * 2)

static int			***g_options;
static unsigned char	**g_active;
static int			*g_trail;
static int			g_trail_top;
static int			g_counts[LINES];
static int			g_limits[LINES];

static void	remove_option(int line, int i)
{
	g_active[line][i] = 0;
	g_counts[line]--;
	g_trail[g_trail_top++] = line * ALL_SOLN + i;
}

static void	rollback(int checkpoint)
{
	int	code;
	int	line;

	while (g_trail_top > checkpoint)
	{
		code = g_trail[--g_trail_top];
		line = code / ALL_SOLN;
		g_active[line][code % ALL_SOLN] = 1;
		g_counts[line]++;
	}
}

static int	cross_line(int line, int pos)
{
	if (line < SIZE)
		return (SIZE + pos);
	return (pos);
}

static int	cross_pos(int line)
{
	if (line < SIZE)
		return (line);
	return (line - SIZE);
}

static void	set_masks(int masks[LINES][SIZE])
{
	int	i;
	int	line;
	int	pos;

	line = 0;
	while (line < LINES)
	{
		pos = 0;
		while (pos < SIZE)
			masks[line][pos++] = 0;
		i = 0;
		while (i < g_limits[line])
		{
			if (g_active[line][i])
			{
				pos = 0;
				while (pos < SIZE)
				{
					masks[line][pos] |= 1 << g_options[line][i][pos];
					pos++;
				}
			}
			i++;
		}
		line++;
	}
}

static int	is_supported(int masks[LINES][SIZE], int line, int *option)
{
	int	pos;

	pos = 0;
	while (pos < SIZE)
	{
		if (!(masks[cross_line(line, pos)][cross_pos(line)]
			& (1 << option[pos])))
			return (0);
		pos++;
	}
	return (1);
}

static int	prune_domains(int masks[LINES][SIZE])
{
	int	changed;
	int	i;
	int	line;

	changed = 0;
	line = 0;
	while (line < LINES)
	{
		i = 0;
		while (i < g_limits[line])
		{
			if (g_active[line][i]
				&& !is_supported(masks, line, g_options[line][i]))
			{
				remove_option(line, i);
				changed = 1;
			}
			i++;
		}
		if (g_counts[line] == 0)
			return (-1);
		line++;
	}
	return (changed);
}

static int	propagate(void)
{
	int	masks[LINES][SIZE];
	int	changed;

	changed = 1;
	while (changed > 0)
	{
		set_masks(masks);
		changed = prune_domains(masks);
	}
	return (changed == 0);
}

static int	select_line(void)
{
	int	best;
	int	line;
	int	selected;

	best = ALL_SOLN + 1;
	selected = -1;
	line = 0;
	while (line < LINES)
	{
		if (g_counts[line] == 0)
			return (-2);
		if (g_counts[line] > 1 && g_counts[line] < best)
		{
			best = g_counts[line];
			selected = line;
		}
		line++;
	}
	return (selected);
}

static void	restrict_line(int line, int keep)
{
	int	i;

	i = 0;
	while (i < g_limits[line])
	{
		if (i != keep && g_active[line][i])
			remove_option(line, i);
		i++;
	}
}

static int	print_solution(void)
{
	int	board[SIZE][SIZE];
	int	col;
	int	i;
	int	row;

	row = 0;
	while (row < SIZE)
	{
		i = 0;
		while (!g_active[row][i])
			i++;
		col = 0;
		while (col < SIZE)
		{
			board[row][col] = g_options[row][i][col];
			col++;
		}
		row++;
	}
	return (print_board(board));
}

static int	solve_state(void)
{
	int	checkpoint;
	int	i;
	int	line;

	line = select_line();
	if (line == -1)
		return (print_solution());
	if (line == -2)
		return (0);
	i = 0;
	while (i < g_limits[line])
	{
		if (g_active[line][i])
		{
			checkpoint = g_trail_top;
			restrict_line(line, i);
			if (propagate() && solve_state())
				return (1);
			rollback(checkpoint);
		}
		i++;
	}
	return (0);
}

static int	malloc_state(int ***options, int *counts)
{
	int	i;
	int	total;

	g_options = options;
	g_active = malloc((size_t)LINES * sizeof(unsigned char *));
	if (!g_active)
		return (0);
	total = 0;
	i = 0;
	while (i < LINES)
		total += counts[i++];
	g_active[0] = malloc((size_t)total * sizeof(unsigned char));
	g_trail = malloc((size_t)total * sizeof(int));
	if (!g_active[0] || !g_trail)
		return (0);
	return (1);
}

static void	set_state(int *counts)
{
	int	i;
	int	j;

	g_trail_top = 0;
	i = 0;
	while (i < LINES)
	{
		g_counts[i] = counts[i];
		g_limits[i] = counts[i];
		if (i > 0)
			g_active[i] = g_active[i - 1] + g_limits[i - 1];
		j = 0;
		while (j < g_limits[i])
			g_active[i][j++] = 1;
		i++;
	}
}

static void	free_state(void)
{
	if (g_active)
	{
		free(g_active[0]);
		free(g_active);
	}
	free(g_trail);
	g_active = 0;
	g_trail = 0;
}

int	solve(int ***options, int *counts)
{
	int	result;

	if (!malloc_state(options, counts))
	{
		free_state();
		return (0);
	}
	set_state(counts);
	result = propagate() && solve_state();
	free_state();
	return (result);
}
