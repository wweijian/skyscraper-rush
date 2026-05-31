/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:18 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 22:58:35 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	int		**solution;
	int		***options;
	int		counts[SIZE * 2];
	int		rules[SIDES][SIZE];
	int		result;

	result = 0;
	if (ac != 2
		|| SIZE > MAX_SIZE
		|| !validate_args(av[1], rules))
		return (print_error());
	if (!malloc_solution(&solution))
		return (print_error());
	if (!malloc_options(&options))
	{
		free_solution(solution);
		return (print_error());
	}
	set_solution(solution);
	set_options(options, counts, solution, rules);
	result = solve(options, counts);
	free_options(options);
	free_solution(solution);
	if (!result)
		return (print_error());
	return (0);
}
