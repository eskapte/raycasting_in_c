/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:16:31 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 16:16:31 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_txts(t_win *win, t_txts *txts)
{
	txts->img = mlx_xpm_file_to_image(win->mlx, txts->src, &txts->width,
			&txts->height);
	txts->addr = mlx_get_data_addr(txts->img, &txts->bpp, &txts->l_len,
			&txts->en);
}

static	void	init_game(t_game **game)
{
	t_win	*win;
	int		sizex;
	int		sizey;

	win = callocl(1, sizeof(t_win));
	(*game)->win = win;
	win->mlx = mlx_init();
	if ((*game)->w < 640)
		(*game)->w = 640;
	if ((*game)->h < 480)
		(*game)->h = 480;
	if ((*game)->w > 1920 || (*game)->h > 1080)
	{
		(*game)->w = 1920;
		(*game)->h = 1080;
	}
	win->win = mlx_new_window(win->mlx, (*game)->w, (*game)->h, "Cub3d");
	win->img = mlx_new_image(win->mlx, (*game)->w, (*game)->h);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->l_len, &win->en);
	(*game)->d_rays = callocl((*game)->w + 1, sizeof(float));
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	int		i;

	if (argc < 2 || (argc == 3 && ft_strncmp(argv[2], "--save",
				ft_strlen(argv[2])) || argc > 3))
		exit_with_error("malo ili mnogo argumentov");
	i = 0;
	game = callocl(1, sizeof(t_game));
	parser(argv[1], &game);
	init_game(&game);
	if (argv[2] && !ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		screenshoot(game);
	while (i < 5)
		get_txts(game->win, &game->txts[i++]);
	render(game);
	mlx_hook(game->win->win, 2, 1L << 0, plr_move, game);
	mlx_loop(game->win->mlx);
}
