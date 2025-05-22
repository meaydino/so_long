/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:08 by meaydino          #+#    #+#             */
/*   Updated: 2024/11/21 11:58:48 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = -1;
	while (s[++len])
		if (ft_putchar(s[len]) == -1)
			return (-1);
	return (len);
}

int	ft_putnbr(int n)
{
	int	len;
	int	ctrl;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		len = ft_putchar('-');
		if (len == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		ctrl = ft_putnbr(n / 10);
		if (ctrl == -1)
			return (-1);
		len += ctrl;
	}
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	return (len + 1);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len = ft_unsigned_putnbr(n / 10);
		if (len == -1)
			return (-1);
	}
	if (write(1, &"0123456789"[n % 10], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_puthex(unsigned long n, char c)
{
	char	*hex_chars;
	int		len;

	len = 0;
	if (c == 'X')
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 16)
	{
		len = ft_puthex(n / 16, c);
		if (len == -1)
			return (-1);
		n = n % 16;
	}
	if (ft_putchar(hex_chars[n]) == -1)
		return (-1);
	return (len + 1);
}
