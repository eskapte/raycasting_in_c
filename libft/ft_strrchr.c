/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 03:15:57 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/22 12:55:22 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ch;

	ch = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			ch = (char *)s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (ch);
}
