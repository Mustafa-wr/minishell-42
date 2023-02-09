/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 02:22:06 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/11 06:42:29 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n <= 2147483647)
	{
		if (n < 0)
		{
			if (n == -2147483648)
				return (ft_putstr_fd("-2147483648", fd));
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n <= 9)
			ft_putchar_fd(n + '0', fd);
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
}
int main(void)
{
  int a = 99;

  ft_putnbr_fd(a, 1);
}