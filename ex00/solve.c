/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:42:57 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 19:21:11 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	validate_input(t_condition *condition, t_pos *pos,
							int (*board)[SIZE][SIZE], t_input *input)
{
	return (1);
}

int	solve(t_condition *condition, t_pos *pos, t_input *input, int **solution)
{
	int			i;
	static int	board[SIZE][SIZE];

	i = 0;
	while (i < SIZE)
	{
		
		i++;
	}
	return (0);
}

// how do i prevent rechecking of the lines left and right
// check left + right
// check duplicate and check min-max