/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:27 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:29 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "lib/libft/libft.h"

static int	ft_count_chr(t_state *state, char c)
{
	int	count;
	int	h;
	int	w;

	h = 0;
	count = 0;
	while (h < state->map->height)
	{
		w = 0;
		while (w < state->map->width)
		{
			if (c == state->map->board[h][w])
				count++;
			ft_set_items(state, w, h);
			w++;
		}
		h++;
	}
	return (count);
}

static int	ft_count_chr_map(t_map *map, char c)
{
	int	count;
	int	h;
	int	w;

	h = 0;
	count = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if (c == map->board[h][w])
				count++;
			w++;
		}
		h++;
	}
	return (count);
}

static void	ft_check_chars(t_state *state)
{
	int	h;
	int	w;

	h = 0;
	while (h < state->map->height)
	{
		w = 0;
		while (w < state->map->width)
		{
			if (!ft_strchr(M_ELEMENTS, state->map->board[h][w]))
				ft_exiterr(17, "invalid map, unexpected character", state);
			w++;
		}
		h++;
	}
}

static void	ft_check_game(t_state *state)
{
	t_map	tmp;
	int		i;

	tmp.height = state->map->height;
	tmp.width = state->map->width;
	i = 0;
	tmp.board = (char **) ft_calloc(tmp.height, sizeof(char *));
	if (!tmp.board)
		ft_exiterr(21, "tmp.board cannot be allocated", state);
	while (i < tmp.height)
	{
		tmp.board[i] = ft_strdup(state->map->board[i]);
		i++;
	}
	ft_fill_flood(state->player.x, state->player.y, &tmp);
	if ((ft_count_chr_map(&tmp, M_PLAYER) != 0)
		|| (ft_count_chr_map(&tmp, M_EXIT) != 0)
		|| (ft_count_chr_map(&tmp, M_COLLECTIBLE) != 0))
		ft_exiterr(21, "invalid map, unreachable character", state);
	i = 0;
	while (i < tmp.height)
		free(tmp.board[i++]);
}

void	ft_check_elements(t_state *state)
{
	ft_check_chars(state);
	if (ft_count_chr(state, M_PLAYER) != 1)
		ft_exiterr(18, "invalid player count", state);
	if (ft_count_chr(state, M_EXIT) != 1)
		ft_exiterr(19, "invalid exit count", state);
	state->collectibles = ft_count_chr(state, M_COLLECTIBLE);
	if (state->collectibles < 1)
		ft_exiterr(20, "invalid collectible count", state);
	ft_check_game(state);
}
