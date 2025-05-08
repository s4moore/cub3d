/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:32:00 by ssukhova          #+#    #+#             */
/*   Updated: 2024/01/05 12:07:54 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*to_find;
	char	*str;

	to_find = (char *) little;
	str = (char *) big;
	if (big == NULL && len == 0)
		return (NULL);
	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while ((str [i + j] == to_find [j])
			&& (str [i + j] != '\0' && i + j < len))
		{
			if (to_find [j + 1] == '\0')
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
