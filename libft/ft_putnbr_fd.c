/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:04:33 by jseidere          #+#    #+#             */
/*   Updated: 2024/07/02 13:37:40 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += write (fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		n = -n;
		len += ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		len += ft_putchar_fd(n + 48, fd);
	}
	return (len);
}

/* int main ()
{
  ft_putnbr_fd(-2147483648, 1);
} */