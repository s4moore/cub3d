/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:12 by ssukhova          #+#    #+#             */
/*   Updated: 2024/01/03 17:10:42 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ul(unsigned long n, char const *base)
{
	char			*buffer;
	const size_t	bufsize = ft_get_buffer_size(n, ft_strlen(base)) + 1;
	int				printed;

	printed = 0;
	buffer = (char *)malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (0);
	ft_ultoa_buf_base(n, buffer, bufsize - 1, base);
	buffer[bufsize -1] = '\0';
	printed = ft_print_str(buffer);
	free (buffer);
	return (printed);
}

int	ft_print_ptr(unsigned long long n, char const *base)
{
	size_t	bufsize;
	char	*buffer;
	int		printed;

	printed = 0;
	if (!n)
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		return (5);
	}
	bufsize = ft_get_buffer_size(n, ft_strlen(base)) + 2;
	buffer = (char *)malloc(sizeof(char) * bufsize + 1);
	if (!buffer)
		return (0);
	buffer[0] = '0';
	buffer[1] = 'x';
	ft_ultoa_buf_base(n, buffer + 2, bufsize - 2, base);
	buffer[bufsize] = '\0';
	printed = ft_print_str(buffer);
	free(buffer);
	return (printed);
}
