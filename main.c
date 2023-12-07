/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:04:41 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:04:43 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "lib/libmlx/mlx.h"
#include "so_long.h"

static void	ft_init_state(t_state *state)
{
	state->mlx = NULL;
	state->win = NULL;
	state->map = NULL;
	state->imgs.c = NULL;
	state->imgs.e = NULL;
	state->imgs.o1 = NULL;
	state->imgs.p = NULL;
	state->imgs.z0 = NULL;
	state->collectibles = 0;
	state->player.moves = 0;
}

static void	ft_window(t_state *state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
		ft_exiterr(32, "mlx cannot be initialized", state);
	state->win = mlx_new_window(state->mlx, state->map->width * 64,
			state->map->height * 64, "s o _ l o n g");
	if (!state->win)
		ft_exiterr(33, "window cannot be opened", state);
	ft_init_images(state);
	ft_put_imgs(state);
	mlx_key_hook(state->win, ft_key_hook, state);
	mlx_hook(state->win, BTN_EXIT, 0, ft_exit_game, state);
	mlx_loop(state->mlx);
}

int	main(int ac, char **av)
{
	t_state	*state;

	if (ac != 2)
		ft_exiterr(1, "invalid argument", NULL);
	state = (t_state *) malloc(sizeof(t_state));
	if (!state)
		ft_exiterr(2, "state cannot be allocated", state);
	ft_init_state(state);
	ft_check_map(state, av[1]);
	if (state->map->height > 20 || state->map->width > 40)
		ft_exiterr(31, "map is too big in order to play", state);
	ft_window(state);
}
