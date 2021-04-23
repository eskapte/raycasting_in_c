/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:04:19 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/22 16:04:19 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_r(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (*line == 'R')
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 3)
				exit_with_error("invalid resolution");
			(*game)->w = ft_atoi(splited[1]);
			(*game)->h = ft_atoi(splited[2]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("resolution doesn't exist");
}

void	find_no(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "NO", 2))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2 || open(splited[1], O_RDONLY) < 0)
				exit_with_error("invalid texture path");
			(*game)->txts[1].src = ft_strdup(splited[1]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("some texture path doesn't exist");
}

void	find_so(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "SO", 2))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2 || open(splited[1], O_RDONLY) < 0)
				exit_with_error("invalid texture path");
			(*game)->txts[0].src = ft_strdup(splited[1]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("some texture path doesn't exist");
}

void	find_we(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "WE", 2))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2 || open(splited[1], O_RDONLY) < 0)
				exit_with_error("invalid texture path");
			(*game)->txts[3].src = ft_strdup(splited[1]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("some texture path doesn't exist");
}

void	find_ea(t_game **game, t_list *map_data)
{
	char	*line;
	char	**splited;
	int		i;

	i = 0;
	while (map_data)
	{
		line = ft_strtrim(map_data->content, " ");
		if (!ft_strncmp(line, "EA", 2))
		{
			splited = ft_split(line, ' ');
			if (arr_len(splited) != 2 || open(splited[1], O_RDONLY) < 0)
				exit_with_error("invalid texture path");
			(*game)->txts[2].src = ft_strdup(splited[1]);
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return ;
		}
		map_data = map_data->next;
		free(line);
	}
	exit_with_error("some texture path doesn't exist");
}
