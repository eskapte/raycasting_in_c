#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1201
# define HEIGHT 801
# define SCALE 16
//# define W 119
//# define S 115
//# define D 100
//# define A 97
# define W 1731
# define S 1753
# define D 1751
# define A 1734
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define STEP 3

# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>

typedef struct s_plr
{
	float		x;
	float		y;
	float		dir;
}				t_plr;

typedef struct s_ray
{
	int			old_x;
	int			old_y;
	float		x;
	float		y;
	float		dir;
	float		delta_x;
	float		delta_y;
	float		hitx;
	float		hity;
}				t_ray;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	unsigned int *img;
	char		*addr;
	int			l_len;
	int			bpp;
	int			en;
}				t_win;

typedef struct s_txts
{
	void		*addr;
	int			l_len;
	int			bpp;
	char		*src;
	void		*img;
	int			height;
	int			width;
	int			en;
}				t_txts;

typedef struct s_sprt
{
	float		x;
	float		y;
	float		width;
	float		height;
	float		h_offset;
	float		v_offset;
}				t_sprt;

typedef struct s_line
{
	float		sky;
	float		wall;
	int			x;
	int			j;
}				t_line;

typedef struct s_game
{
	t_win		*win;
	t_plr		*plr;
	t_txts		*txts;
	char		**map;
	t_list		*sprites;
	float		*d_rays;
	int			w;
	int			h;
	int			f_color;
	int			c_color;
}				t_game;

void	exit_with_error(char *e_text);
void	*callocl(size_t nmemb, size_t size);
void	parser(char *map, t_game **game);
void	*create_plr(int x, int y, float dir, t_game **game);
float	get_d(float x1, float y1, float x2, float y2);
int		int_to_hex(int r, int g, int b);
void	draw_line(t_game *game, float dst, int x, t_ray *ray);
void	ray_cast(t_game *game);
void	draw_line(t_game *game, float dst, int x, t_ray *ray);
void	render(t_game *game);
void	plr_move(int kc, t_game *game);
void	add_sprite(t_list **sptires, int x, int y);
void	draw_sprite(t_game **game, t_sprt *sprt);
int		get_pixel(t_game **game, int x, int y, int i);
void	sort_sprites(t_game **game, float x, float y);
void	pixel_put(t_win *win, int x, int y, int color);
int		arr_len(char **arr);
void	find_r(t_game **game, t_list *map_data);
void	find_no(t_game **game, t_list *map_data);
void	find_so(t_game **game, t_list *map_data);
void	find_we(t_game **game, t_list *map_data);
void	find_ea(t_game **game, t_list *map_data);
void	find_s(t_game **game, t_list *map_data);
void	find_floor(t_game **game, t_list *map_data);
void	find_ceil(t_game **game, t_list *map_data);
void	check_player_inside(char **map, t_plr *plr);
void	screenshoot(t_game *game);

#endif