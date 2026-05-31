/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:27:44 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 22:39:13 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdlib.h>

int	validate_solution(int solution[SIZE], int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (solution[i] == solution[pos])
			return (0);
		i++;
	}
	return (1);
}

void	copy_array(int *dst, int *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	fill_solution(int **solution, int *current, int pos, int *count)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		current[pos] = i;
		if (validate_solution(current, pos))
		{
			if (pos == SIZE - 1)
			{
				copy_array(solution[*count], current, SIZE);
				(*count)++;
			}
			else
				fill_solution(solution, current, pos + 1, count);
		}
		i++;
	}
}

void	set_solution(int **solution)
{
	int	count;
	int	current[SIZE];

	count = 0;
	fill_solution(solution, current, 0, &count);
}

int	malloc_solution(int ***solution)
{
	int	i;

	*solution = malloc((size_t)ALL_SOLN * sizeof(int *));
	if (!*solution)
		return (0);
	(*solution)[0] = malloc((size_t)ALL_SOLN * SIZE * sizeof(int));
	if (!(*solution)[0])
	{
		free(*solution);
		return (0);
	}
	i = 1;
	while (i < ALL_SOLN)
	{
		(*solution)[i] = (*solution)[0] + i * SIZE;
		i++;
	}
	return (1);
}

void	free_solution(int **solution)
{
	if (solution)
	{
		free(solution[0]);
		free(solution);
	}
}

int	malloc_options(int ****options)
{
	int	i;

	*options = malloc((size_t)SIZE * 2 * sizeof(int **));
	if (!*options)
		return (0);
	(*options)[0] = malloc((size_t)SIZE * 2 * ALL_SOLN * sizeof(int *));
	if (!(*options)[0])
	{
		free(*options);
		return (0);
	}
	i = 1;
	while (i < SIZE * 2)
	{
		(*options)[i] = (*options)[0] + i * ALL_SOLN;
		i++;
	}
	return (1);
}

void	free_options(int ***options)
{
	if (options)
	{
		free(options[0]);
		free(options);
	}
}

static int	valid_for_line(int *solution, int line, int rules[SIDES][SIZE])
{
	if (line < SIZE)
		return (check_left(solution, rules[LEFT][line])
			&& check_right(solution, rules[RIGHT][line]));
	line -= SIZE;
	return (check_left(solution, rules[TOP][line])
		&& check_right(solution, rules[BOTTOM][line]));
}

void	set_options(int ***options, int *counts, int **solution,
		int rules[SIDES][SIZE])
{
	int	line;
	int	i;

	line = 0;
	while (line < SIZE * 2)
	{
		counts[line] = 0;
		i = 0;
		while (i < ALL_SOLN)
		{
			if (valid_for_line(solution[i], line, rules))
				options[line][counts[line]++] = solution[i];
			i++;
		}
		line++;
	}
}
