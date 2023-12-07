/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:04:17 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:04:20 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define M_ENEMY 'X'
# define M_WALL '1'
# define M_GROUND '0'
# define M_COLLECTIBLE 'C'
# define M_PLAYER 'P'
# define M_EXIT 'E'
# define M_ELEMENTS "X10CPE"

# define BTN_EXIT 17

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_R 15
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

# define DIR_LEFT 	42
# define DIR_RIGHT 	31
# define DIR_UP 	21
# define DIR_DOWN 	1337

typedef struct s_map
{
	char	*path;
	int		width;
	int		height;
	char	**board;
}				t_map;

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
	int	current_img;
}			t_player;

typedef struct s_exit
{
	int	x;
	int	y;
}			t_exit;

typedef struct s_imgs
{
	void	*e;
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	void	*p5;
	void	*p6;
	void	*o1;
	void	*z0;
	void	*c;
	void	*x;
}			t_imgs;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				direction;
	struct s_enemy	*next;
}			t_enemy;

typedef struct s_state
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	player;
	t_enemy		*enemies;
	t_imgs		imgs;
	int			collectibles;
	t_exit		exit;
}				t_state;

void	ft_exiterr(int err_no, char *err, t_state *state);
void	ft_dispose(t_state *state);
void	ft_check_map(t_state *state, char *map_path);
int		ft_strlen_endl(char *str);
void	ft_check_elements(t_state *state);
void	ft_fill_flood(int x, int y, t_map *map);
void	ft_init_images(t_state *state);
int		ft_exit_game(t_state *state);
int		ft_key_hook(int key, t_state *state);
void	ft_put_imgs(t_state *state);
void	ft_set_items(t_state *state, int w, int h);
int		ft_loop_hook(t_state *state);
void	ft_move_enemies(t_state *state, int change_dir);
void	ft_player_anim(t_state *state);
void	ft_check_collision(t_state *state);
void	ft_write_score(t_state *state);
void	ft_set_enemies(t_state *state);

#endif
