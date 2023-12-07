/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:03:45 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:03:48 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	ft_check_width(t_state *state, int old_width, char *line)
{
	if (!line)
		return ;
	if (old_width != ft_strlen_endl(line))
		ft_exiterr(12, "invalid map, line lengths are incompatible", state);
}

void	ft_fill_flood(int x, int y, t_map *map)
{
	if (x < 0 || x > map->width - 1 || y < 0 || y > map->height - 1)
		return ;
	if (map->board[y][x] != '1' && map->board[y][x] != 'F')
	{
		map->board[y][x] = 'F';
		ft_fill_flood(x, y - 1, map);
		ft_fill_flood(x, y + 1, map);
		ft_fill_flood(x - 1, y, map);
		ft_fill_flood(x + 1, y, map);
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
