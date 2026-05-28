/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:06 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 00:58:50 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static inline int	ft_is_valid_num(char c)
{
	return (c >= '1' && c <= '9' && c - '0' <= SIZE);
}

int	validate_args(char *arg, int rules[SIDES][SIZE])
{
	int	i;

	i = 0;
	while (i < SIZE * SIDES * 2 - 1)
	{
		if (!arg[i])
			return (0);
		if (i % 2 == 0)
		{
			if (!ft_is_valid_num(arg[i]))
				return (0);
			rules[i / 2 / SIZE][i / 2 % SIZE] = arg[i] - '0';
		}
		else if (i % 2 != 0 && arg[i] != ' ')
			return (0);
		i++;
	}
	return (arg[i] == 0);
}

/* 
	rule structure:

	top		top		top		top
	down	down	down	down
	left	left	left	left
	right	right	right	right
*/
