/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:44:54 by weijian           #+#    #+#             */
/*   Updated: 2026/05/28 00:18:31 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	check_visibility(int value, int *tallest)
{
	if (value > *tallest)
	{
		*tallest = value;
		return (1);
	}
	return (0);
}

int	tallest_remainder(int remainder[SIZE])
{
	int	i;

	i = SIZE - 1;
	while (i >= 0)
	{
		if (remainder[i] == 1)
			return (i);
		i++;
	}
	return (0);
}