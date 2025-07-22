/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:51:46 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/06 21:17:24 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	long long	nbl;

	nbl = n;
	if (nbl < 0)
	{
		write(fd, "-", 1);
		nbl = -nbl;
	}
	if (nbl > 9)
	{
		ft_putnbr_fd(nbl / 10, fd);
	}
	c = (nbl % 10) + '0';
	write(fd, &c, 1);
	return ;
}
/*int	main(void)
{
	ft_putnbr_fd(1337, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(111111, 0);
	write(1, "\n", 1);
	ft_putnbr_fd(8122036, 2);
	write(1, "\n", 1);
	return (0);
}*/
