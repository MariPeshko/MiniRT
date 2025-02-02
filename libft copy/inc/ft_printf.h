/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:16:21 by sgramsch          #+#    #+#             */
/*   Updated: 2023/12/14 15:16:21 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr(int n, int size);
int	ft_putstr(char *s);
int	ft_putchar(unsigned char c);
int	ft_hexa(long long int n, int size, int up);
int	ft_putunsigned(unsigned int n, int size);

#endif
