/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:41:03 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 18:00:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putstr(int fd, char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}

int	ft_putchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_putposnbr(int fd, unsigned long n, int uppercase, unsigned long base)
{
	int	len;

	len = 0;
	if (n >= base)
		len += ft_putposnbr(fd, n / base, uppercase, base);
	if ((n % base) < 10)
		ft_putchar(fd, '0' + (n % base));
	else
		ft_putchar(fd, ('a' + (n % base - 10) + uppercase * ('A' - 'a')));
	len ++;
	return (len);
}

int	ft_putnbr(int fd, long long n, t_printfp params)
{
	int				len;
	unsigned long	l;

	if (params.pointeur && n == 0)
		return (write(fd, "(nil)", 5));
	l = n;
	len = 0;
	if (params.pointeur)
		len += write(fd, "0x", 2);
	if (n < 0 && params.base == 10)
	{
		len += write(fd, "-", 1);
		l = -n;
	}
	if (params.pointeur)
		l = (unsigned long)n;
	else if (params.base == 16)
		l = (unsigned long)((unsigned int)n);
	return (len + (ft_putposnbr(fd, l, params.uppercase, params.base)));
}
