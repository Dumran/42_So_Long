/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:04:53 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:42:23 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "lib/libmlx/mlx.h"

static void	ft_put_img(t_state *state, char c, int x, int y)
{
	if (c != M_WALL)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.z0, x, y);
	if (c == M_WALL)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.o1, x, y);
	if (c == M_PLAYER)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.p, x, y);
	if (c == M_COLLECTIBLE)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.c, x, y);
	if (c == M_EXIT)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.e, x, y);
}

void	ft_put_imgs(t_state *state)
{
	int	h;
	int	w;

	h = 0;
	while (h < state->map->height)
	{
		w = 0;
		while (w < state->map->width)
		{
			ft_put_img(state, state->map->board[h][w], w * 64, h * 64);
			w++;
		}
		h++;
	}
}

void	ft_init_images(t_state *state)
{
	int	x;
	int	y;

	state->imgs.p = mlx_xpm_file_to_image(state->mlx,
			"textures/player1.xpm", &x, &y);
	if (!state->imgs.p)
		ft_exiterr(34, "'textures/player1.xpm' file cannot be found", state);
	state->imgs.e = mlx_xpm_file_to_image(state->mlx,
			"textures/exit.xpm", &x, &y);
	if (!state->imgs.e)
		ft_exiterr(35, "'textures/exit.xpm' file cannot be found", state);
	state->imgs.c = mlx_xpm_file_to_image(state->mlx,
			"textures/diamond.xpm", &x, &y);
	if (!state->imgs.c)
		ft_exiterr(36, "'textures/diamond.xpm' file cannot be found", state);
	state->imgs.z0 = mlx_xpm_file_to_image(state->mlx,
			"textures/floor.xpm", &x, &y);
	if (!state->imgs.z0)
		ft_exiterr(37, "'textures/floor.xpm' file cannot be found", state);
	state->imgs.o1 = mlx_xpm_file_to_image(state->mlx,
			"textures/wall.xpm", &x, &y);
	if (!state->imgs.o1)
		ft_exiterr(38, "'textures/wall.xpm' file cannot be found", state);
}
