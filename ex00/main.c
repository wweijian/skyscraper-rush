/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:18 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 15:22:27 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int			rules[SIDES][SIZE];
	t_condition	conditions;
	t_pos		start_pos;
	t_input		input;
	int			**solution;

	if (ac != 2
		|| SIZE > MAX_SIZE
		|| !validate_args(av[1], rules)
		|| !malloc_solution(&solution))
		return (print_error());
	conditions = set_conditions(rules);
	start_pos = set_start_pos();
	input = set_input();
	solution = set_solution(solution);
	if (!solve(&conditions, &start_pos, &input, solution))
		return (print_error());
	return (0);
}
