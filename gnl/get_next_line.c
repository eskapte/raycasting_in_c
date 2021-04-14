/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:13:51 by lhawick           #+#    #+#             */
/*   Updated: 2021/03/12 16:14:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*join_or_create(char **temp, char *buff, int cnt)
{
	char	*new_temp;

	new_temp = (*temp) ? ft_strjoin(*temp, buff) : ft_substr(buff, 0, cnt);
	if (*temp)
		free(*temp);
	return (new_temp);
}

static	int		get_index_n(char *buff)
{
	int	i;

	if (!buff)
		return (-1);
	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static	char	*use_temp(char *temp, char **line)
{
	int		index_n;
	char	*t_temp;

	index_n = get_index_n(temp);
	if (index_n == 0)
	{
		*line = ft_substr("", 0, 1);
		t_temp = ft_substr(temp, 1, ft_strlen(temp));
		free(temp);
		return (t_temp);
	}
	if (index_n != -1)
	{
		*line = ft_substr(temp, 0, index_n);
		t_temp = ft_substr(temp, index_n + 1, ft_strlen(temp));
		free(temp);
		temp = NULL;
		return (t_temp);
	}
	return (temp);
}

static	int		read_file(int fd, char **temp, char **line)
{
	int		cnt;
	char	*buff;

	buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((cnt = read(fd, buff, BUFFER_SIZE)) >= 0 && !(*line))
	{
		buff[cnt] = '\0';
		*temp = join_or_create(temp, buff, cnt);
		*temp = use_temp(*temp, line);
		if (cnt == 0)
			return (return_and_free(&buff, 0));
		if (!(*temp) && cnt < BUFFER_SIZE)
			return (return_and_free(&buff, 0));
		if (*line)
			return (return_and_free(&buff, 1));
	}
	return (return_and_free(&buff, 0));
}

int				get_next_line(int fd, char **line)
{
	static	char	*temp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, "", 0) < 0)
		return (-1);
	*line = NULL;
	if (temp)
		temp = use_temp(temp, line);
	if (*line)
		return (1);
	if (read_file(fd, &temp, line))
		return (1);
	if (temp)
	{
		temp = use_temp(temp, line);
		if (!temp)
			return (0);
		if (*line)
			return (1);
		*line = ft_substr(temp, 0, ft_strlen(temp));
		temp_free(&temp);
		return (0);
	}
	return (-1);
}
