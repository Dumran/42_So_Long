/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:00 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:44:57 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "lib/libmlx/mlx.h"

static void	ft_put_player_img_to_window(t_state *state, int x, int y)
{
	if (state->player.current_img == 1)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.p1, x, y);
	if (state->player.current_img == 2)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.p2, x, y);
	if (state->player.current_img == 3)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.p3, x, y);
	if (state->player.current_img == 4)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.p4, x, y);
}

static void	ft_put_img(t_state *state, char c, int x, int y)
{
	if (c != M_WALL)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.z0, x, y);
	if (c == M_WALL)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.o1, x, y);
	if (c == M_PLAYER)
		ft_put_player_img_to_window(state, x, y);
	if (c == M_COLLECTIBLE)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.c, x, y);
	if (c == M_EXIT)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.e, x, y);
	if (c == M_ENEMY)
		mlx_put_image_to_window(state->mlx, state->win, state->imgs.x, x, y);
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

static void	ft_init_player_imgs(t_state *state, int *x, int *y)
{
	state->imgs.p1 = mlx_xpm_file_to_image(state->mlx,
			"textures/player1.xpm", x, y);
	if (!state->imgs.p1)
		ft_exiterr(38, "'textures/player1.xpm' file cannot be found", state);
	state->imgs.p2 = mlx_xpm_file_to_image(state->mlx,
			"textures/player2.xpm", x, y);
	if (!state->imgs.p2)
		ft_exiterr(39, "'textures/player2.xpm' file cannot be found", state);
	state->imgs.p3 = mlx_xpm_file_to_image(state->mlx,
			"textures/player3.xpm", x, y);
	if (!state->imgs.p3)
		ft_exiterr(40, "'textures/player3.xpm' file cannot be found", state);
	state->imgs.p4 = mlx_xpm_file_to_image(state->mlx,
			"textures/player4.xpm", x, y);
	if (!state->imgs.p4)
		ft_exiterr(41, "'textures/player4.xpm' file cannot be found", state);
	state->imgs.p5 = mlx_xpm_file_to_image(state->mlx,
			"textures/player5.xpm", x, y);
}

void	ft_init_images(t_state *state)
{
	int	x;
	int	y;

	ft_init_player_imgs(state, &x, &y);
	state->imgs.e = mlx_xpm_file_to_image(state->mlx,
			"textures/exit.xpm", &x, &y);
	if (!state->imgs.e)
		ft_exiterr(34, "'textures/exit.xpm' file cannot be found", state);
	state->imgs.c = mlx_xpm_file_to_image(state->mlx,
			"textures/diamond.xpm", &x, &y);
	if (!state->imgs.c)
		ft_exiterr(35, "'textures/diamond.xpm' file cannot be found", state);
	state->imgs.z0 = mlx_xpm_file_to_image(state->mlx,
			"textures/floor.xpm", &x, &y);
	if (!state->imgs.z0)
		ft_exiterr(36, "'textures/floor.xpm' file cannot be found", state);
	state->imgs.o1 = mlx_xpm_file_to_image(state->mlx,
			"textures/wall.xpm", &x, &y);
	if (!state->imgs.o1)
		ft_exiterr(37, "'textures/wall.xpm' file cannot be found", state);
	state->imgs.x = mlx_xpm_file_to_image(state->mlx,
			"textures/enemy.xpm", &x, &y);
	if (!state->imgs.x)
		ft_exiterr(44, "'textures/enemy.xpm' file cannot be found", state);
}
