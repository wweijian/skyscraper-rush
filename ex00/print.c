/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:41 by weijian           #+#    #+#             */
/*   Updated: 2026/05/27 21:38:16 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>

int	print_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

void	print_conditions(t_condition *condition)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE) {
			printf("pos: (%d, %d):\t", i, j);
			fflush(stdout);
			c = condition->top[i][j] + '0';
			write(1, &c, 1);
			write(1, ", ", 2);
			c = condition->bottom[i][j] + '0';
			write(1, &c, 1);
			write(1, ", ", 2);
			c = condition->left[i][j] + '0';
			write(1, &c, 1);
			write(1, ", ", 2);
			c = condition->right[i][j] + '0';
			write(1, &c, 1);
			write(1, "\n", 1);
			j++;
		}
		i++;
	}
}

int	print_board(t_board board)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE) {
			c = board[i][j] + '0';
			write(1, &c, 1);
			if (j != SIZE - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
	}
	return (1);
}