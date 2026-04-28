/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:31:06 by pserre-s          #+#    #+#             */
/*   Updated: 2025/11/19 13:45:17 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	check_format(char conv, va_list ap)
{
	void	*ptr;

	if (conv == 'c')
		return (ft_printf_putchar(va_arg(ap, int)));
	else if (conv == 's')
		return (ft_printf_str(va_arg(ap, char *)));
	else if (conv == 'p')
	{
		ptr = va_arg(ap, void *);
		if (ptr == 0)
			return (ft_printf_str("(nil)"));
		return (ft_printf_str("0x") + ft_printf_putnbr_hex((uintptr_t)ptr, 0));
	}
	else if (conv == 'd' || conv == 'i')
		return (ft_printf_putnbr(va_arg(ap, int)));
	else if (conv == 'u')
		return (ft_printf_putnbr_unsigned(va_arg(ap, unsigned int)));
	else if (conv == 'x')
		return (ft_printf_putnbr_hex((uintptr_t)va_arg(ap, unsigned int), 0));
	else if (conv == 'X')
		return (ft_printf_putnbr_hex((uintptr_t)va_arg(ap, unsigned int), 1));
	else if (conv == '%')
		return (ft_printf_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		char_count;

	i = 0;
	char_count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			char_count += check_format(format[i], ap);
		}
		else
			char_count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (char_count);
}
