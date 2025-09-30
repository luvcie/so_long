/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:31:44 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 17:53:56 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	(void)write(fd, s, ft_strlen(s));
	(void)write(fd, "\n", 1);
}

/*int	main(void)
{
	ft_putendl_fd("nosce te ipsum", 1);
	return (0);
}*/
