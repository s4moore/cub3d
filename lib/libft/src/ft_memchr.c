/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:24:49 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/17 14:07:04 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;
	char	a;

	p = (char *) s;
	a = (char) c;
	i = 0;
	while (i < n)
	{
		if (p[i] == a)
			return ((void *)p + i);
		i++;
	}
	return (NULL);
}
