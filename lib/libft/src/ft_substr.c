/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:50:07 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/21 16:46:23 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			sublen;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) > len)
		sublen = len;
	else
		sublen = ft_strlen(s) - start;
	sub = (char *)malloc(sublen + 1);
	if (!sub)
		return (NULL);
	while (s[start] != '\0' && i < sublen)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
