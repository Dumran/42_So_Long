/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:47 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:49 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "so_long.h"
#include "lib/libmlx/mlx.h"
#include "lib/libft/libft.h"

int	ft_exit_game(t_state *state)
{
	mlx_destroy_window(state->mlx, state->win);
	ft_dispose(state);
	ft_printf("exited\n");
	exit(EXIT_SUCCESS);
}

static int	ft_check_next_tile(t_state *state, int direction, char tile)
{
	if (direction == DIR_RIGHT)
	{
		if (state->map->board[state->player.y][state->player.x + 1] == tile)
			return (1);
	}
	else if (direction == DIR_LEFT)
	{
		if (state->map->board[state->player.y][state->player.x - 1] == tile)
			return (1);
	}
	else if (direction == DIR_DOWN)
	{
		if (state->map->board[state->player.y + 1][state->player.x] == tile)
			return (1);
	}
	else if (direction == DIR_UP)
	{
		if (state->map->board[state->player.y - 1][state->player.x] == tile)
			return (1);
	}
	return (0);
}

static int	ft_check_move(t_state *state, int direction)
{
	if (ft_check_next_tile(state, direction, M_WALL))
		return (0);
	if (ft_check_next_tile(state, direction, M_COLLECTIBLE))
		state->collectibles--;
	if (ft_check_next_tile(state, direction, M_EXIT)
		&& state->collectibles == 0)
	{
		state->player.moves++;
		ft_printf("you won!\ntotal moves: %d\n", state->player.moves);
		ft_exit_game(state);
	}
	state->player.moves++;
	ft_printf("moves: %d\n", state->player.moves);
	return (1);
}

static void	ft_move(t_state *state, int direction)
{
	if (!ft_check_move(state, direction))
		return ;
	if (state->player.x == state->exit.x
		&& state->player.y == state->exit.y)
		state->map->board[state->player.y][state->player.x] = M_EXIT;
	else
		state->map->board[state->player.y][state->player.x] = M_GROUND;
	if (direction == DIR_RIGHT)
		state->player.x++;
	else if (direction == DIR_LEFT)
		state->player.x--;
	else if (direction == DIR_DOWN)
		state->player.y++;
	else if (direction == DIR_UP)
		state->player.y--;
	state->map->board[state->player.y][state->player.x] = M_PLAYER;
}

int	ft_key_hook(int key, t_state *state)
{
	if (key == KEY_ESC)
		ft_exit_game(state);
	else if (key == KEY_A || key == KEY_LEFT)
		ft_move(state, DIR_LEFT);
	else if (key == KEY_D || key == KEY_RIGHT)
		ft_move(state, DIR_RIGHT);
	else if (key == KEY_W || key == KEY_UP)
		ft_move(state, DIR_UP);
	else if (key == KEY_S || key == KEY_DOWN)
		ft_move(state, DIR_DOWN);
	ft_put_imgs(state);
	return (0);
}
