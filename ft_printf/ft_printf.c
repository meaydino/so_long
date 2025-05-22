/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:21:14 by meaydino          #+#    #+#             */
/*   Updated: 2024/11/21 14:23:30 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_check(char c, va_list arg, void *ptr, int len)
{
	if (c == '%')
		return (ft_putchar('%'));
	if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	if (c == 'u')
		return (ft_unsigned_putnbr(va_arg(arg, unsigned int)));
	if (c == 'X' || c == 'x')
		return (ft_puthex(va_arg(arg, unsigned int), c));
	if (c == 'p')
	{
		ptr = va_arg(arg, void *);
		if (ptr == NULL)
			return (ft_putstr("(nil)"));
		if (write(1, "0x", 2) == -1)
			return (-1);
		len = ft_puthex((unsigned long)ptr, 'x');
		if (len == -1)
			return (-1);
		return (len + 2);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;
	int		ctrl;
	int		i;

	len = -1;
	i = -1;
	va_start(arg, format);
	if (!format)
		return (-1);
	while (len++, format[++i])
	{
		if (format[i] == '%')
		{
			if (!format[++i])
				return (va_end(arg), len);
			ctrl = ft_check(format[i], arg, 0, 0);
			if (ctrl == -1)
				return (-1);
			len += ctrl - 1;
		}
		else if (write(1, &format[i], 1) == -1)
			return (va_end(arg), -1);
	}
	return (va_end(arg), len);
}
