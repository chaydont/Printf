/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:51:28 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 19:33:16 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	n_digit(intmax_t n, int base)
{
	int i;

	i = 1;
	if (base < 2 || n == 0)
		return (0);
	while ((n >= base || n <= -base) && i++ >= 0)
		n /= base;
	return (i);
}

static void	ft_printnr(intmax_t n, t_param flags, int first, int *j)
{
	int size;

	if (first)
	{
		size = n_digit(n, 10);
		if (n < 0 && size)
			write(1, "-", 1);
		else if (flags.plus)
			write(1, "+", 1);
		else if (flags.space)
			write(1, " ", 1);
		*j += flags.precision > size ? flags.precision - size : 0;
		while (flags.precision-- - size > 0)
			write(1, "0", 1);
		if (!n)
			return ;
	}
	if (n < 10 && n > -10)
	{
		ft_putchar(n > 0 ? n + '0' : -n + '0');
		(*j)++;
		return ;
	}
	ft_printnr(n / 10, flags, 0, j);
	ft_printnr(n % 10, flags, 0, j);
}

static int	ft_length(intmax_t n, t_param flags, int size)
{
	int i;
	int j;
	int pre;

	i = 0;
	j = 0;
	pre = n < 0 || flags.space || flags.plus ? 1 : 0;
	if (flags.zero && flags.precision == -1 && !flags.minus)
		flags.precision = flags.length - pre;
	if (flags.precision == -1)
		flags.precision = 1;
	flags.precision < size ? flags.precision = size : 0;
	if (!flags.minus)
		while (flags.length > flags.precision + pre + i++)
			write(1, " ", 1);
	ft_printnr(n, flags, 1, &j);
	if (flags.minus)
		while (flags.length > flags.precision + pre + i++)
			write(1, " ", 1);
	return (i + j + pre - 1);
}

int			ft_printi(va_list ap, t_param flags)
{
	intmax_t	n;
	int			size;
	int			pre;

	if (flags.flag == 'z')
		n = va_arg(ap, size_t);
	else if (flags.flag == 'l')
		n = va_arg(ap, long);
	else if (flags.flag == 'L')
		n = va_arg(ap, long long);
	else
		n = (flags.flag == 'j' ? va_arg(ap, intmax_t) : va_arg(ap, int));
	if (flags.flag == 'H')
		n = (char)n;
	else
		n = flags.flag == 'h' ? (short)n : n;
	size = n_digit(n, 10);
	return (ft_length(n, flags, size));
}
