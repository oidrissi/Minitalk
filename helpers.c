/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:09:35 by oidrissi          #+#    #+#             */
/*   Updated: 2021/06/18 07:04:04 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*v;

	v = b;
	while (len > 0)
	{
		len--;
		*(v++) = c;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	int		help;
	long	longn;

	longn = (long)n;
	if (longn < 0)
	{
		ft_putchar('-');
		longn = -1 * longn;
	}
	if (longn <= 9)
		ft_putchar(longn + 48);
	else
	{
		help = longn % 10;
		ft_putnbr(longn / 10);
		ft_putchar(help + 48);
	}
}
