/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:52 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:53 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "lib/libft/libft.h"

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
	ft_loop_hook(state);
	return (0);
}

int	ft_loop_hook(t_state *state)
{
	static unsigned int	i = 1;
	static int			change_dir = 0;

	if (i % 500 == 0)
		change_dir = 1;
	else
		change_dir = 0;
	if (i % 15 == 0)
		ft_move_enemies(state, change_dir);
	if (i % 5 == 0)
		ft_player_anim(state);
	ft_check_collision(state);
	ft_put_imgs(state);
	ft_write_score(state);
	i++;
	return (0);
}
