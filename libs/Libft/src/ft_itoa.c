/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:13:25 by pserre-s          #+#    #+#             */
/*   Updated: 2025/11/06 17:46:54 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long nbr)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nbr;
	int		len;

	nbr = (long)n;
	len = ft_nbrlen(nbr);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		result[0] = '-';
	}
	if (nbr == 0)
		result[0] = '0';
	while (nbr > 0)
	{
		len--;
		result[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}
