/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:18:02 by octoross          #+#    #+#             */
/*   Updated: 2024/02/02 22:58:34 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

size_t	ft_strlen(char *s);
int		ft_strcmp(const char *s1, char *s2);
int		ft_putnbr(int fd, long long n, int uppercase, unsigned long base, int p);
int		ft_putstr(int fd, char *s);
int		ft_putchar(int fd, char c);

int		ft_printf(int fd, const char *format, ...);

#endif