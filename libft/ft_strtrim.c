/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:16:14 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/22 13:17:47 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inlist(char const ch, char const *set)
{
	while (*set != '\0')
	{
		if (*set == ch)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	j;
	unsigned int	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (inlist(s1[i], set) && i < ft_strlen(s1))
		i++;
	if (i == ft_strlen(s1))
		return (ft_substr("", 0, 1));
	j = ft_strlen(s1) - 1;
	while (inlist(s1[j], set) && j >= i)
		j--;
	if (j >= i)
		return (ft_substr(s1, i, j - i + 1));
	return (ft_substr("", 0, 1));
}
