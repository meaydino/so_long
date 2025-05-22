/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:16:54 by meaydino          #+#    #+#             */
/*   Updated: 2024/11/21 11:58:43 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *format, ...);
int	ft_puthex(unsigned long n, char c);
int	ft_unsigned_putnbr(unsigned int n);
int	ft_putnbr(int n);
int	ft_putstr(char *s);
int	ft_putchar(char c);

#endif
