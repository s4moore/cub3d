/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:23:37 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/17 15:14:15 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	dlen;

	dlen = ft_strlen(s) + 1;
	d = (char *)malloc(dlen);
	if (!d)
		return (NULL);
	ft_strlcpy (d, s, dlen);
	return (d);
}
