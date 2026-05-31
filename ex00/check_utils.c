/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:44:54 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 18:20:24 by weijian          ###   ########.fr       */
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
