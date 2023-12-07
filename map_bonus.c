/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:04:32 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:04:34 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "stdlib.h"
#include "lib/libft/libft.h"
#include "so_long_bonus.h"

static void	ft_check_width(t_state *state, int old_width, char *line)
{
	if (!line)
		return ;
	if (old_width != ft_strlen_endl(line))
		ft_exiterr(12, "invalid map, line lengths are incompatible", state);
}

static void	ft_check_border(t_state *state)
{
	int	x;
	int	y;

	y = 0;
	while (y < state->map->height)
	{
		x = 0;
		if (y == 0 || y == state->map->height - 1)
		{
			while (x < state->map->width)
				if (state->map->board[y][x++] != M_WALL)
					ft_exiterr(14, "invalid map border", state);
		}
		else
		{
			if (state->map->board[y][x] != M_WALL
				|| state->map->board[y][state->map->width - 1] != M_WALL)
				ft_exiterr(16, "invalid map border", state);
		}
		y++;
	}
}

static void	ft_set_boundaries(t_state *state)
{
	int		height;
	int		width;
	char	*line;
	int		fd;

	fd = open(state->map->path, O_RDONLY);
	if (fd == -1)
		ft_exiterr(6, "map cannot be opened", state);
	height = 0;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (width != 0)
			ft_check_width(state, width, line);
		width = ft_strlen_endl(line);
		height++;
		free(line);
	}
	if (close(fd) == -1)
		ft_exiterr(7, "map file cannot be closed", state);
	state->map->height = height;
	state->map->width = width;
}

void	ft_init_map(t_state *state, char *map_path)
{
	char	*line;
	int		fd;
	int		i;

	state->map->path = map_path;
	ft_set_boundaries(state);
	fd = open(state->map->path, O_RDONLY);
	if (fd == -1)
		ft_exiterr(8, "map cannot be opened", state);
	state->map->board = (char **) malloc(state->map->height * sizeof(char *));
	if (!state->map->board)
		ft_exiterr(9, "state.map.board cannot be allocated", state);
	i = 0;
	while (i < state->map->height)
	{
		line = get_next_line(fd);
		if (!line)
			ft_exiterr(10, "map line cannot be read", state);
		state->map->board[i] = line;
		if (!state->map->board[i])
			ft_exiterr(11, "state.map.board item cannot be allocated", state);
		i++;
	}
	if (close(fd) == -1)
		ft_exiterr(15, "map file cannot be closed", state);
}

void	ft_check_map(t_state *state, char *map_path)
{
	char	*file_ext;

	if (!map_path)
		ft_exiterr(3, "map path cannot be null", state);
	file_ext = ft_strnstr(map_path, ".ber", ft_strlen(map_path));
	if (!file_ext || ft_strncmp(file_ext, ".ber", ft_strlen(file_ext)) != 0)
		ft_exiterr(4, "invalid map file, need a file with '.ber'", state);
	state->map = (t_map *) ft_calloc(1, sizeof(t_map));
	if (!state->map)
		ft_exiterr(5, "state.map cannot be allocated", state);
	ft_init_map(state, map_path);
	ft_check_border(state);
	ft_check_elements(state);
}
