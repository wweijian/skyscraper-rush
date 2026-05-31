/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 22:12:47 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 20:44:40 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	check_left(int *row, int rule)
{
	int	i;
	int	tallest;
	int	visibility;

	i = 0;
	tallest = -1;
	visibility = 0;
	while (i < SIZE)
	{
		visibility += check_visibility(row[i], &tallest);
		i++;
	}
	return (visibility == rule);
}

int	check_right(int *row, int rule)
{
	int	i;
	int	tallest;
	int	visibility;

	i = SIZE - 1;
	tallest = -1;
	visibility = 0;
	while (i >= 0)
	{
		visibility += check_visibility(row[i], &tallest);
		i--;
	}
	return (visibility == rule);
}
