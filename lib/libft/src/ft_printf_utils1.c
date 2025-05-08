/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:35:14 by ssukhova          #+#    #+#             */
/*   Updated: 2024/01/05 17:14:53 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (1);
}

int	ft_print_int(int n)
{
	char	*str;
	int		i;

	str = ft_itoa(n);
	i = ft_strlen(str);
	ft_putstr_fd(str, STDOUT_FILENO);
	free (str);
	return (i);
}

int	ft_print_str(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr_fd("(null)", STDOUT_FILENO);
		return (6);
	}
	i = ft_strlen(str);
	ft_putstr_fd(str, STDOUT_FILENO);
	return (i);
}

int	ft_get_buffer_size(unsigned long n, size_t radix)
{
	int	i;

	i = 0;
	while (n >= radix)
	{
		n = n / radix;
		i++;
	}
	return (++i);
}

int	ft_ultoa_buf_base(unsigned long n, char *buffer,
		size_t bufsize, char const *base)
{
	const size_t	radix = ft_strlen(base);
	size_t			i;

	i = bufsize;
	while (n >= radix)
	{
		buffer[--i] = base[n % radix];
		n = n / radix;
	}
	buffer[--i] = base[n];
	return (bufsize);
}
