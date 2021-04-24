/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:58:35 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/23 17:58:35 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_inside(char **map, t_plr *plr)
{
	int		px;
	int		py;
	char	*str;
	int		i;

	i = 0;
	if (!plr || !map)
		exit_with_error("i dont know whats happened");
	px = (int)(plr->x / SCALE);
	py = (int)(plr->y / SCALE);
	str = ft_strtrim(map[py], " \t");
	if (!str)
		exit_with_error("i dont know whats happened");
	if (*str != '1')
		exit_with_error("player doesn't inside the map");
	if (str[ft_strlen(str) - 1] != '1')
		exit_with_error("player doesn't inside the map");
	free(str);
	while (map[i][px] && map[i][px] != '1')
		if (i++ == py)
			exit_with_error("player doesn't inside the map");
	i = py;
	while (map[i][px])
		if (map[i++][px] == '1')
			return ;
	exit_with_error("player doesn't inside the map");
}
