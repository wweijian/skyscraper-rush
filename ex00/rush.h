/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:46 by weijian           #+#    #+#             */
/*   Updated: 2026/05/31 22:36:57 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

# ifndef SIZE
#  define SIZE 4
#  define ALL_SOLN 24
# elif SIZE == 4
#  define ALL_SOLN 24
# elif SIZE == 5
#  define ALL_SOLN 120
# elif SIZE == 6
#  define ALL_SOLN 720
# elif SIZE == 7
#  define ALL_SOLN 5040
# elif SIZE == 8
#  define ALL_SOLN 40320
# elif SIZE == 9
#  define ALL_SOLN 362880
# else
#  error "Unsupported SIZE"
# endif

# define MAX_SIZE 9
# define SIDES 4

# define TOP 0
# define BOTTOM 1
# define LEFT 2
# define RIGHT 3

// validate.c
int		validate_args(char *arg, int rules[SIDES][SIZE]);

// print.c
int		print_error(void);
int		print_board(int board[SIZE][SIZE]);

// check_utils.c
int		check_visibility(int value, int *tallest);

// check_horizontal.c
int		check_left(int *row, int rule);
int		check_right(int *row, int rule);

// set_solutions.c
int		malloc_solution(int ***solution);
void	free_solution(int **solution);
void	set_solution(int **solution);
int		malloc_options(int ****options);
void	free_options(int ***options);
void	set_options(int ***options, int *counts, int **solution,
			int rules[SIDES][SIZE]);

// solve.c
int		solve(int ***options, int *counts);

#endif
