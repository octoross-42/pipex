/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:21:22 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 18:01:16 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_error_format(const char *format)
{
	int	i;
	int	nbr_successive_pourcents;

	nbr_successive_pourcents = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (i == 0 || format[i - 1] != '%')
				nbr_successive_pourcents = 1;
			else
				nbr_successive_pourcents ++;
		}
		else
			nbr_successive_pourcents = 0;
		i ++;
	}
	if (format[i - 1] == '%' && (nbr_successive_pourcents % 2))
		return (1);
	return (0);
}

static t_printfp	ft_params(int uppercase, unsigned long base, int pointeur)
{
	t_printfp	params;

	params.uppercase = uppercase;
	params.base = base;
	params.base = pointeur;
	return (params);
}

static int	ft_format(int fd, char c, va_list *ap, int *i)
{
	if (c == 'c')
		return (ft_putchar(fd, (char)va_arg(*ap, int)));
	else if (c == 's')
		return (ft_putstr(fd, va_arg(*ap, char *)));
	else if (c == 'p')
		return (ft_putnbr(fd, va_arg(*ap, unsigned long), ft_params(0, 16, 1)));
	else if (c == 'd')
		return (ft_putnbr(fd, va_arg(*ap, int), ft_params(0, 10, 0)));
	else if (c == 'i')
		return (ft_putnbr(fd, va_arg(*ap, int), ft_params(0, 10, 0)));
	else if (c == 'u')
		return (ft_putnbr(fd, va_arg(*ap, unsigned int), ft_params(0, 10, 0)));
	else if (c == 'x')
		return (ft_putnbr(fd, va_arg(*ap, int), ft_params(0, 16, 0)));
	else if (c == 'X')
		return (ft_putnbr(fd, va_arg(*ap, int), ft_params(1, 16, 0)));
	else if (c == '%')
		return (ft_putchar(fd, '%'));
	else
	{
		(*i)--;
		return (ft_putchar(fd, '%'));
	}
	return (0);
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	ap;
	int		i;
	int		len;

	if (fd < 0 || !format || ft_error_format(format))
		return (-1);
	len = 0;
	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			len += ft_format(fd, format[++ i], &ap, &i);
		else
			len += ft_putchar(fd, format[i]);
		i ++;
	}
	va_end(ap);
	return (len);
}
