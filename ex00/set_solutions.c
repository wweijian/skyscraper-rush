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

int	**set_solution(int ***solution, int pos)
{
	int			i;
	static int	count = 0;
	static int	current[SIZE];

	i = 0;
	while (i < SIZE)
	{
		current[pos] = i;
		if (validate_solution(current, pos))
		{
			if (pos == SIZE - 1)
			{
				copy_array((*solution)[count], current, SIZE);
				count++;
			}
			else
				set_solution(solution, pos + 1);
		}
		i++;
	}
	return (*solution);
}

int	malloc_solution(int ***solution)
{
	int	i;

	i = 0;
	*solution = malloc((size_t)ALL_SOLN * sizeof(int *));
	if (!*solution)
		return (0);
	i = 0;
	while (i < ALL_SOLN)
	{
		(*solution)[i] = malloc((size_t)SIZE * sizeof(int));
		if ((*solution)[i] == NULL)
		{
			while (i >= 0)
			{
				free((*solution)[i]);
				i--;
			}
			free(*solution);
			return (0);
		}
		i++;
	}
	return (1);
}
