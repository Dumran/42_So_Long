/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:03:52 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:23:44 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "so_long_bonus.h"

int	ft_strlen_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	ft_fill_flood(int x, int y, t_map *map)
{
	if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
		return ;
	if (map->board[y][x] != M_WALL && map->board[y][x] != 'F')
	{
		map->board[y][x] = 'F';
		ft_fill_flood(x, y - 1, map);
		ft_fill_flood(x, y + 1, map);
		ft_fill_flood(x - 1, y, map);
		ft_fill_flood(x + 1, y, map);
	}
}

static void	ft_set_enemy(t_state *state, int h, int w)
{
	t_enemy	*tmp;

	if (!state->enemies)
	{
		state->enemies = (t_enemy *) malloc(sizeof(t_enemy));
		if (!state->enemies)
			ft_exiterr(45, "state.enemies cannot be allocated", state);
		state->enemies->x = w;
		state->enemies->y = h;
		state->enemies->direction = DIR_RIGHT;
		state->enemies->next = NULL;
	}
	else
	{
		tmp = state->enemies;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_enemy *) malloc(sizeof(t_enemy));
		if (!tmp->next)
			ft_exiterr(46, "state.enemies cannot be allocated", state);
		tmp->next->x = w;
		tmp->next->y = h;
		tmp->next->direction = DIR_RIGHT;
		tmp->next->next = NULL;
	}
}

void	ft_set_items(t_state *state, int w, int h)
{
	if (state->map->board[h][w] == M_PLAYER)
	{
		state->player.x = w;
		state->player.y = h;
		state->player.moves = 0;
	}
	if (state->map->board[h][w] == M_EXIT)
	{
		state->exit.x = w;
		state->exit.y = h;
	}
}

void	ft_set_enemies(t_state *state)
{
	int	h;
	int	w;

	h = 0;
	while (h < state->map->height)
	{
		w = 0;
		while (w < state->map->width)
		{
			if (M_ENEMY == state->map->board[h][w])
				ft_set_enemy(state, h, w);
			w++;
		}
		h++;
	}
}
