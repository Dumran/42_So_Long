/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:22 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:24 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_remove_enemies_from_map(t_state *state)
{
	int	h;
	int	w;

	h = 0;
	while (h < state->map->height)
	{
		w = 0;
		while (w < state->map->width)
		{
			if (state->map->board[h][w] == M_ENEMY)
				state->map->board[h][w] = M_GROUND;
			w++;
		}
		h++;
	}
}

static void	ft_put_enemies_to_map(t_state *state)
{
	t_enemy	*enemy;

	enemy = state->enemies;
	ft_remove_enemies_from_map(state);
	while (enemy)
	{
		state->map->board[enemy->y][enemy->x] = M_ENEMY;
		enemy = enemy->next;
	}
}

static void	ft_move_enemy(t_state *state, t_enemy *enemy, int x, int y)
{
	if (state->map->board[y][x] == M_WALL
		|| state->map->board[y][x] == M_COLLECTIBLE
		|| state->map->board[y][x] == M_EXIT
		|| state->map->board[y][x] == M_ENEMY)
	{
		if (enemy->direction == DIR_RIGHT)
			enemy->direction = DIR_UP;
		else if (enemy->direction == DIR_LEFT)
			enemy->direction = DIR_DOWN;
		else if (enemy->direction == DIR_DOWN)
			enemy->direction = DIR_RIGHT;
		else if (enemy->direction == DIR_UP)
			enemy->direction = DIR_LEFT;
	}
	else
	{
		enemy->x = x;
		enemy->y = y;
	}
	ft_put_enemies_to_map(state);
}

static void	ft_move_enemies_directed(t_state *state, t_enemy *enemy)
{
	if (enemy->direction == DIR_RIGHT)
	{
		enemy->direction = DIR_UP;
		ft_move_enemy(state, enemy, enemy->x, enemy->y + 1);
	}
	else if (enemy->direction == DIR_LEFT)
	{
		enemy->direction = DIR_DOWN;
		ft_move_enemy(state, enemy, enemy->x, enemy->y - 1);
	}
	else if (enemy->direction == DIR_DOWN)
	{
		enemy->direction = DIR_RIGHT;
		ft_move_enemy(state, enemy, enemy->x - 1, enemy->y);
	}
	else if (enemy->direction == DIR_UP)
	{
		enemy->direction = DIR_LEFT;
		ft_move_enemy(state, enemy, enemy->x + 1, enemy->y);
	}
}

void	ft_move_enemies(t_state *state, int change_dir)
{
	t_enemy	*enemy;

	enemy = state->enemies;
	while (enemy)
	{
		if (change_dir == 0)
		{
			if (enemy->direction == DIR_RIGHT)
				ft_move_enemy(state, enemy, enemy->x + 1, enemy->y);
			else if (enemy->direction == DIR_LEFT)
				ft_move_enemy(state, enemy, enemy->x - 1, enemy->y);
			else if (enemy->direction == DIR_DOWN)
				ft_move_enemy(state, enemy, enemy->x, enemy->y + 1);
			else if (enemy->direction == DIR_UP)
				ft_move_enemy(state, enemy, enemy->x, enemy->y - 1);
		}
		else
			ft_move_enemies_directed(state, enemy);
		enemy = enemy->next;
	}
}
