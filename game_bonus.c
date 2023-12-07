/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:05 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:31:42 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "so_long_bonus.h"
#include "lib/libft/libft.h"
#include "lib/libmlx/mlx.h"

void	ft_check_collision(t_state *state)
{
	t_enemy	*enemy;

	enemy = state->enemies;
	while (enemy)
	{
		if (enemy->x == state->player.x && enemy->y == state->player.y)
		{
			ft_printf("you lost!\n");
			ft_printf("Total points: %d\n", state->player.moves);
			ft_exit_game(state);
		}
		enemy = enemy->next;
	}
}

void	ft_player_anim(t_state *state)
{
	if (state->player.current_img == 1)
		state->player.current_img = 2;
	else if (state->player.current_img == 2)
		state->player.current_img = 3;
	else if (state->player.current_img == 3)
		state->player.current_img = 4;
	else if (state->player.current_img == 4)
		state->player.current_img = 5;
	else if (state->player.current_img == 5)
		state->player.current_img = 6;
	else if (state->player.current_img == 6)
		state->player.current_img = 1;
}

int	ft_exit_game(t_state *state)
{
	mlx_destroy_window(state->mlx, state->win);
	ft_dispose(state);
	ft_printf("exited\n");
	exit(EXIT_SUCCESS);
}

void	ft_write_score(t_state *state)
{
	char	*score;
	char	*tmp;

	score = ft_itoa(state->player.moves);
	tmp = ft_strjoin("Score: ", score);
	mlx_string_put(state->mlx, state->win, 31, 31, 0x00FF0000, tmp);
	free(score);
	free(tmp);
}
