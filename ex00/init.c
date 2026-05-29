/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: weijian <weijian@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/05/29 10:43:39 by weijian		   #+#	#+#			 */
/*   Updated: 2026/05/29 10:58:50 by weijian		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "rush.h"
#include <stdio.h>
#include <stdlib.h>

t_condition	set_conditions(int rules[SIDES][SIZE])
{
	t_condition	conditions;
	int			i;
	int			j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			conditions.top[i][j] = rules[0][j];
			conditions.bottom[i][j] = rules[1][j];
			conditions.left[i][j] = rules[2][i];
			conditions.right[i][j] = rules[3][i];
			j++;
		}
		i++;
	}
	return (conditions);
}

t_pos	set_start_pos(void)
{
	t_pos	pos;

	pos.row = 0;
	pos.col = 0;
	return (pos);
}

t_input	set_input(void)
{
	t_input	input;
	int		i;
	int		j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			input.horizontal[i][j] = 1;
			input.vertical[i][j] = 1;
			j++;
		}
		i++;
	}
	return (input);
}

int	malloc_solution(int*** solution)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (++i <= SIZE)
		n *= i;
	*solution = malloc((size_t)n * sizeof(int *));
	i = 0;
	while (i < n)
	{
		(*solution)[i] = malloc((size_t)SIZE * sizeof(int));
		if ((*solution)[i] == NULL)
		{
			while (i >= 0)
			{
				free((*solution)[i]);
				i--;
			}
			free(solution);
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_appeared_map(int appeared_map[SIZE])
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		appeared_map[i] = 0;
		i++;
	}
	return ;
}