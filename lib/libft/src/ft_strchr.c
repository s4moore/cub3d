/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:27:15 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/21 15:57:08 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	unc;

	unc = (unsigned char)c;
	while ((*s != '\0') && (*s != unc))
	{
		s++;
	}
	if (*s == unc)
		return ((char *)s);
	return (NULL);
}
