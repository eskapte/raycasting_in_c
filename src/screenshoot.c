/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshoot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 23:48:47 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/24 23:48:47 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_pix(t_game *game, int line, int *x, int y)
{
	char	save;
	int		i;

	i = 4;
	while (--i >= 0)
	{
		save = game->win->addr[*x + line * game->win->l_len];
		game->win->addr[*x + line * game->win->l_len]
			= game->win->addr[y - i + (line * game->win->l_len - 1)];
		game->win->addr[y - i + (line * game->win->l_len - 1)] = save;
		(*x)++;
	}
}

static void	line(t_game *game)
{
	int	line;
	int	x;
	int	y;

	line = -1;
	while (++line < game->h)
	{
		x = 0;
		y = game->win->l_len;
		while (x < y)
		{
			get_pix(game, line, &x, y);
			y -= 4;
		}
	}
}

static void	file_name(t_game *game, int fd)
{
	int	size;
	int	n;

	size = 4096;
	n = 1;
	write(fd, &size, 4);
	write(fd, &game->w, 4);
	write(fd, &game->h, 4);
	write(fd, &n, 2);
	write(fd, &game->win->bpp, 2);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

void	screenshoot(t_game *game)
{
	int	fd;
	int	size;
	int	i;
	int	j;

	fd = open("sh.bmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
	if (fd < 0)
		exit_with_error("failed to create screenshoot");
	size = 14 + 40 + game->w * game->h * 4;
	i = 14 + 40;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &i, 4);
	file_name(game, fd);
	line(game);
	j = game->h - 1;
	while (j >= 0)
		write(fd, &game->win->addr[j-- *game->win->bpp / 8], 4);
	close(fd);
	exit(0);
}
