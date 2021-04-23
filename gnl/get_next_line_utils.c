/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:13:53 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/22 13:43:53 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*start_substr;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	substr = malloc(len + 1);
	if (substr == 0)
		return (0);
	start_substr = substr;
	while (s[start] != '\0' && i < len)
	{
		*substr = s[start++];
		substr++;
		i++;
	}
	*substr = '\0';
	return (start_substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*start_newstr;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == 0)
		return (0);
	start_newstr = newstr;
	while (*s1 != '\0')
	{
		*newstr = *s1;
		newstr++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*newstr = *s2;
		newstr++;
		s2++;
	}
	*newstr = '\0';
	return (start_newstr);
}

void	temp_free(char **temp)
{
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
}

int	return_and_free(char **need_free, int need_return)
{
	if (*need_free)
	{
		free(*need_free);
		*need_free = NULL;
	}
	return (need_return);
}
