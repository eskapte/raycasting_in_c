/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:24:21 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/22 21:24:21 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_s(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "S ", 2))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2 || open(splited[1], O_RDONLY) < 0)
				exit_with_error("invalid sprite path");
			(*game)->txts[4].src = ft_strdup(splited[1]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("sprite path doesn't exist");
}

static int	str_to_hex(char *str)
{
	char	**splited;
	short	r;
	short	g;
	short	b;

	splited = ft_split(str, ',');
	if (!splited || arr_len(splited) != 3)
		return (0);
	r = (short)ft_atoi(splited[0]);
	g = (short)ft_atoi(splited[1]);
	b = (short)ft_atoi(splited[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b <0 || b > 255)
		return (0);
	return (int_to_hex(r, g, b));
}

void	find_floor(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "F", 1))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2)
				exit_with_error("invalid floor color");
			(*game)->f_color = str_to_hex(splited[1]);
			if ((*game)->f_color == 0)
				exit_with_error("invalid floor color");
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("floor color doesn't exist");
}

void	find_ceil(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "C", 1))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2)
				exit_with_error("invalid ceil color");
			(*game)->c_color = str_to_hex(splited[1]);
			if ((*game)->c_color == 0)
				exit_with_error("invalid ceil color");
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("ceil color doesn't exist");
}
