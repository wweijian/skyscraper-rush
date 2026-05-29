/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:27:44 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 15:11:34 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int validate_solution(int solution[SIZE], int pos)
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

void	print_array(int *arr)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
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

int **set_solution(int ***solution, int pos)
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
				print_array((*solution)[count]);
				count++;
			}
			else
			{
				set_solution(solution, pos + 1);
			}
		}
		i++;
	}
	return (*solution);
}
