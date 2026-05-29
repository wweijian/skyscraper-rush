/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:46 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 12:45:26 by weijian          ###   ########.fr       */
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

typedef struct s_pos
{
	int	row;
	int	col;
}	t_pos;

typedef struct s_condition
{
	int	left[SIZE][SIZE];
	int	right[SIZE][SIZE];
	int	top[SIZE][SIZE];
	int	bottom[SIZE][SIZE];
}	t_condition;

typedef struct s_input
{
	int	horizontal[SIZE][SIZE];
	int	vertical[SIZE][SIZE];
}	t_input;

// validate.c
int			validate_args(char *arg, int rules[SIDES][SIZE]);

// print.c
int			print_error(void);
int			print_board(int board[SIZE][SIZE]);

// check_utils.c
int			check_visibility(int value, int *tallest);
int			tallest_remainder(int remainder[SIZE]);

// check_board.c
int			check_left(int left[SIZE][SIZE], t_pos *pos,
				int (*board)[SIZE][SIZE],
				t_input *input);
int			check_top(int top[SIZE][SIZE], t_pos *pos,
				int (*board)[SIZE][SIZE],
				t_input *input);
int			check_right(int right[SIZE][SIZE], t_pos *pos,
				int (*board)[SIZE][SIZE],
				t_input *input);
int			check_bottom(int bottom[SIZE][SIZE], t_pos *pos,
				int (*board)[SIZE][SIZE],
				t_input *input);

// init.c
t_condition	set_conditions(int rules[SIDES][SIZE]);
t_pos		set_start_pos(void);
t_input		set_input(void);
int			malloc_solution(int*** solution);
void		set_appeared_map(int appeared_map[SIZE]);

// solve.c
int			solve(t_condition *condition, t_pos *pos, t_input *input);

// solve_utils.c
void		adjust_input(t_input *input, int board[SIZE][SIZE], t_pos *pos,
				int value);
void		return_input(t_input *input, int board[SIZE][SIZE], t_pos *pos,
				int value);
void		go_next_grid(t_pos *pos);
void		restore_grid(t_pos *pos);

// debug
// void	print_conditions(t_condition *condition);
// void	print_rules(int rules[SIDES][SIZE]);

#endif
