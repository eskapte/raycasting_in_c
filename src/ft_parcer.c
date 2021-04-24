/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:48:57 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 17:48:57 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	float	get_dir(char c)
{
	if (c == 'N')
		return (M_PI_2 * 3);
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (M_PI_2);
	if (c == 'W')
		return (M_PI);
	return (0);
}

static	char	**make_map(t_list *lst_map)
{
	char	**map;
	int		i;
	int		len;

	while (lst_map && *(ft_strtrim(lst_map->content, " \t")) != '1')
		lst_map = lst_map->next;
	len = ft_lstsize(lst_map);
	if (len < 3)
		exit_with_error("the map is small or doesn't exist");
	map = callocl(len + 1, sizeof(char *));
	i = 0;
	while (lst_map && *(ft_strtrim(lst_map->content, " \t")) == '1')
	{
		map[i++] = lst_map->content;
		lst_map = lst_map->next;
	}
	if (arr_len(map) < 3)
		exit_with_error("the map is small or doesn't exist");
	return (map);
}

static	void	find_objs(char	**map, t_game **game)
{
	int		y;
	int		x;
	int		c;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			c = map[y][x];
			if ((c == 'N') || (c == 'S') || (c == 'W') || (c == 'E'))
				create_plr(x, y, get_dir(c), game);
			if (c == '2')
				add_sprite(&((*game)->sprites), x, y);
			x++;
		}
		x = 0;
		y++;
	}
	if (!(*game)->plr)
		exit_with_error("the player doesn't exist");
}

static	void	parse_data(t_game **game, t_list *map_data)
{
	find_r(game, map_data);
	find_no(game, map_data);
	find_so(game, map_data);
	find_we(game, map_data);
	find_ea(game, map_data);
	find_s(game, map_data);
	find_floor(game, map_data);
	find_ceil(game, map_data);
}

void	parser(char *map, t_game **game)
{
	t_list	*map_data;
	int		fd;
	int		i;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		exit_with_error("failed to open the file");
	i = get_next_line(fd, &line);
	while (i > 0)
	{
		if (i == -1)
			exit_with_error("failed to read the file");
		ft_lstadd_back(&map_data, ft_lstnew(line));
		i = get_next_line(fd, &line);
	}
	ft_lstadd_back(&map_data, ft_lstnew(line));
	if (ft_lstsize(map_data) < 11)
		exit_with_error("incorrect map");
	(*game)->txts = callocl(5, sizeof(t_txts));
	parse_data(game, map_data);
	(*game)->map = make_map(map_data);
	find_objs((*game)->map, game);
	check_player_inside((*game)->map, (*game)->plr);
	close(fd);
}
