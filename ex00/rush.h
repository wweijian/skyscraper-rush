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

# include <stdio.h>

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

typedef struct s_pos
{
	int	row;
	int	col;
}	t_pos;

typedef enum e_mode
{
	SET,
	GET,
	FREE,
}	t_mode;

// validate.c
int		validate_args(char *arg, int rules[SIDES][SIZE]);

// print.c
int		print_error(void);
int		print_board(int **board);

// check_utils.c
int		check_visibility(int value, int *tallest);
void	zero_appeared(int appeared[SIZE][SIZE]);
int		tallest_remainder(int appeared[SIZE][SIZE], int col);

// check_board.c
int		check_left(int **board, int rules[SIDES][SIZE], int row);
int		check_right(int **board, int rules[SIDES][SIZE], int row);
int		check_vertical(int **board, int rules[SIDES][SIZE], int row);

// set_solution.c
int		malloc_solution(int ***solution);
int		**set_solution(int ***solution, int pos);

// solve.c
int		solve(int **board, int rules[SIDES][SIZE], int row, int **solution);

// debug
// void	print_conditions(t_condition *condition);
// void	print_rules(int rules[SIDES][SIZE]);

#endif
