/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:54:40 by lucpardo          #+#    #+#             */
/*   Updated: 2025/05/05 21:10:50 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}
/*
int	main(void)
{
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('7', 0);
	ft_putchar_fd('5', 1);
	ft_putchar_fd('7', 2);
	ft_putchar_fd('z', 3);
	return (0);
}*/
