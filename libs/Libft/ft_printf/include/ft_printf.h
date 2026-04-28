/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:19:59 by pserre-s          #+#    #+#             */
/*   Updated: 2025/11/15 16:22:44 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);

int	ft_printf_putchar(char c);
int	ft_printf_str(char *str);
int	ft_printf_putnbr(int nbr);
int	ft_printf_putnbr_unsigned(unsigned int nbr);
int	ft_printf_putnbr_hex(uintptr_t nbr, int is_uppercase);
#endif