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
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int		**solution;
	int		**board;
	int		rules[SIDES][SIZE];
	int		result;

	result = 0;
	if (ac != 2
		|| SIZE > MAX_SIZE
		|| !validate_args(av[1], rules)
		|| !malloc_solution(&solution))
		return (print_error());
	board = malloc(sizeof(int *) * SIZE);
	if (board)
	{
		solution = set_solution(&solution, 0);
		result = solve(board, rules, 0, solution);
	}
	free(solution);
	if (!result)
		return(print_error());
	return (0);
}
