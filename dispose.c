/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:37 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:39 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "so_long.h"

static void	ft_dispose_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	if (map->board)
		while (i < map->height)
			free(map->board[i++]);
	free(map->board);
	free(map);
}

void	ft_dispose(t_state *state)
{
	if (!state)
		return ;
	ft_dispose_map(state->map);
}
