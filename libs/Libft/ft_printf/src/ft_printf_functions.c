/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:56:51 by pserre-s          #+#    #+#             */
/*   Updated: 2025/11/14 12:17:08 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_printf_str(char *str)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printf_putnbr(int nbr)
{
	long	n;
	int		count;

	n = nbr;
	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		count += ft_printf_putnbr(n / 10);
	count += ft_printf_putchar((n % 10) + '0');
	return (count);
}

int	ft_printf_putnbr_unsigned(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr > 9)
		count += ft_printf_putnbr_unsigned(nbr / 10);
	count += ft_printf_putchar((nbr % 10) + '0');
	return (count);
}

int	ft_printf_putnbr_hex(uintptr_t nbr, int is_uppercase)
{
	int		count;
	char	*hex;

	count = 0;
	if (is_uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (nbr >= 16)
		count += ft_printf_putnbr_hex(nbr / 16, is_uppercase);
	count += ft_printf_putchar(hex[nbr % 16]);
	return (count);
}
