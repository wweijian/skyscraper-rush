/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:41 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 00:58:01 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>

int	print_error(void)
{
	write(2, "Error\n", 6);
	return (1);
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
		while (j < SIZE)
		{
			c = board[i][j] + '0' + 1;
			write(1, &c, 1);
			if (j != SIZE - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

/* #include <stdio.h>
void	print_conditions(t_condition *condition)
{
	int		i;
	int		j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE) {
			printf("pos: (%d, %d):\t", i, j);
			printf("top: %d, bottom: %d, left: %d, right: %d\n",
				condition->top[i][j],
				condition->bottom[i][j],
				condition->left[i][j],
				condition->right[i][j]);
			j++;
		}
		i++;
	}
	puts("");
} 
	
void	print_rules(t_rules rules)
{
	for (int i = 0; i < SIDES; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%d ", rules[i][j]);
		}
		printf("\n");
	}
}
	
*/