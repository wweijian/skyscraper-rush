/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:18 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 00:58:36 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>

static t_condition	set_conditions(int rules[SIDES][SIZE])
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

static void	initialize(t_condition *conditions, t_pos *pos, t_input *input,
						int rules[SIDES][SIZE])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*conditions = set_conditions(rules);
	pos->row = 0;
	pos->col = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			input->horizontal[i][j] = 1;
			input->vertical[i][j] = 1;
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int			rules[SIDES][SIZE];
	t_condition	conditions;
	t_pos		start_pos;
	t_input		input;

	if (ac != 2 || SIZE > MAX_SIZE || !validate_args(av[1], rules))
		return (print_error());
	initialize(&conditions, &start_pos, &input, rules);
	if (!solve(&conditions, &start_pos, &input))
		return (print_error());
	return (0);
}
