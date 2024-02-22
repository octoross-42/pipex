/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:18:02 by octoross          #+#    #+#             */
/*   Updated: 2024/02/22 18:00:28 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H

# include "utils.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_printfp
{
	int				uppercase;
	unsigned long	base;
	int				pointeur;
}	t_printfp;

int		ft_putnbr(int fd, long long n, t_printfp params);
int		ft_putstr(int fd, char *s);
int		ft_putchar(int fd, char c);

int		ft_printf(int fd, const char *format, ...);

#endif