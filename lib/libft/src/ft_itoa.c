/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:27:08 by ssukhova          #+#    #+#             */
/*   Updated: 2023/11/22 15:04:17 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_malloc(int n, int len)
{
	char	*res;

	if (n == 0)
	{
		res = (char *)malloc(sizeof(char) + 1);
		if (!res)
			return (NULL);
		res[0] = '0';
	}
	else if (n < 0)
	{
		res = (char *)malloc((len + 1) * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '-';
	}
	else
		res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = ft_count(n);
	res = ft_malloc(n, len);
	if (!res)
		return (NULL);
	if (n == -2147483648)
	{
		res[1] = '2';
		n = 147483648;
	}
	if (n < 0)
		n = n * (-1);
	while (n != 0)
	{
		res[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (res);
}
