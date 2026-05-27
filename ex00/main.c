/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:18 by weijian           #+#    #+#             */
/*   Updated: 2026/05/28 00:19:52 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>

static t_condition	set_conditions(t_rules rules)
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
			conditions.top[i][j] = rules[0][i];
			conditions.bottom[i][j] = rules[1][i];
			conditions.left[i][j] = rules[2][j];
			conditions.right[i][j] = rules[3][j];
			j++;
		}
		i++;
	}
	return (conditions);
}

static void initialize(t_condition *conditions, t_pos *pos, t_input *input, t_rules rules)
{
	int	i;

	i = 0;
	*conditions = set_conditions(rules);
	pos->row = 0;
	pos->col = 0;
	input->value = 0;
	while (i < SIZE)
	{
		input->horizontal[i] = 1;
		input->vertical[i] = 1;
		i++;
	}
}

int	main(int ac, char **av)
{
	int			rules[4][SIZE];
	t_condition	conditions;
	t_pos		start_pos;
	t_input		input;

	if (ac != 2 || SIZE > MAX_SIZE || !validate_args(av[1], rules))
		return (print_error());
	write(1, "parse success\n", 14);
	initialize(&conditions, &start_pos, &input, rules);
	return (solve(&conditions, &start_pos, &input) != 1);
}
