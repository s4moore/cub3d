/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:05:50 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/21 16:39:48 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	origsize;
	char	*save;

	origsize = size;
	save = dst;
	while (size-- && *dst)
		dst++;
	lendst = dst - save;
	if (lendst >= origsize)
		return (origsize + ft_strlen(src));
	return (lendst + ft_strlcpy(dst, src, origsize - lendst));
}
