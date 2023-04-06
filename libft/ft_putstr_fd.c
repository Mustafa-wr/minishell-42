/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:34:13 by mradwan           #+#    #+#             */
/*   Updated: 2023/04/02 01:03:18 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd, int parameter)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
	}
	if (parameter == 1)
		write(fd, "\n", 1);
}

/*
int	main(void)
{
	char	x[];

  x[] = "gf5";
   ft_putstr_fd(x, 1);
  return(0);
}
*/
