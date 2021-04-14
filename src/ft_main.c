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

	*game = callocl(1, sizeof(t_game));
	win = callocl(1, sizeof(t_win));
	(*game)->win = win;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "Cub3d");
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->l_len, &win->en);
	(*game)->txts = callocl(4, sizeof(t_txts));
}

int	main(void)
{
	t_game	*game;

	init_game(&game);
	parser("hz", &game);
	game->txts[0].src = "src/img/stone.xpm";
	game->txts[1].src = "src/img/wood.xpm";
	game->txts[2].src = "src/img/diamond.xpm";
	game->txts[3].src = "src/img/creeper.xpm";
	get_txts(game->win, &game->txts[0]);
	get_txts(game->win, &game->txts[1]);
	get_txts(game->win, &game->txts[2]);
	get_txts(game->win, &game->txts[3]);
	render(game);
	mlx_hook(game->win->win, 2, 1L << 0, plr_move, game);
	mlx_loop(game->win->mlx);
}
