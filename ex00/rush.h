/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weijian <weijian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:54:46 by weijian           #+#    #+#             */
/*   Updated: 2026/05/29 01:02:33 by weijian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

# include <stdio.h>

# ifndef SIZE
#  define SIZE 4
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

typedef int	t_rules[SIDES][SIZE];
typedef int	t_existing[SIZE];
typedef int	t_board[SIZE][SIZE];

// validate.c
int		validate_args(char *arg, t_rules rules);

// print.c
int		print_error(void);
int		print_board(t_board board);

// check_utils.c
int		check_visibility(int value, int *tallest);
int		tallest_remainder(int remainder[SIZE]);

// check_board.c
int		check_left(int left[SIZE][SIZE], t_pos *pos, t_board *board,
			t_input *input);
int		check_top(int top[SIZE][SIZE], t_pos *pos, t_board *board,
			t_input *input);
int		check_right(int right[SIZE][SIZE], t_pos *pos, t_board *board,
			t_input *input);
int		check_bottom(int bottom[SIZE][SIZE], t_pos *pos, t_board *board,
			t_input *input);

// solve.c
int		solve(t_condition *condition, t_pos *pos, t_input *input);

// solve_utils.c
void	adjust_input(t_input *input, t_board board, t_pos *pos, int value);
void	return_input(t_input *input, t_board board, t_pos *pos, int value);
void	go_next_grid(t_pos *pos);
void	restore_grid(t_pos *pos);

// debug
// void	print_conditions(t_condition *condition);
// void	print_rules(t_rules rules);

#endif