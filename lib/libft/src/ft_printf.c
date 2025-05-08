/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:17:36 by ssukhova          #+#    #+#             */
/*   Updated: 2024/01/03 16:33:21 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(const char c, va_list *ap)
{
	int	i;

	i = 0;
	if (c == '%')
		i += ft_print_char('%');
	else if (c == 'c')
		i += ft_print_char(va_arg(*ap, int));
	else if (c == 'i' || c == 'd')
		i += ft_print_int(va_arg(*ap, int));
	else if (c == 's')
		i += ft_print_str(va_arg(*ap, char *));
	else if (c == 'u')
		i += ft_print_ul(va_arg(*ap, unsigned int), "0123456789");
	else if (c == 'x')
		i += ft_print_ul(va_arg(*ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		i += ft_print_ul(va_arg(*ap, unsigned int), "0123456789ABCDEF");
	else if (c == 'p')
		i += ft_print_ptr((unsigned long long)va_arg(*ap, void *),
				"0123456789abcdef");
	return (i);
}

int	ft_vprintf(const char *format, va_list *ap, int const isfunction[])
{
	char	c;
	int		i;

	i = 0;
	c = *format;
	while (c != '\0')
	{
		if (c != '%')
		{
			i += ft_print_char(c);
			c = *++format;
		}
		else
		{
			c = *++format;
			if (isfunction[(unsigned char)c])
			{
				i += print_format(c, ap);
				c = *++format;
			}
			else
				ft_putchar_fd('%', STDOUT_FILENO);
		}
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	va_list		arguments;
	int const	isfunction[UCHAR_MAX] = {
	['c'] = 1,
	['%'] = 1,
	['i'] = 1,
	['d'] = 1,
	['s'] = 1,
	['u'] = 1,
	['x'] = 1,
	['X'] = 1,
	['p'] = 1,
	};

	va_start (arguments, format);
	count = ft_vprintf(format, &arguments, isfunction);
	va_end (arguments);
	return (count);
}
