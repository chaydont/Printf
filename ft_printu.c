/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:51:28 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 16:43:04 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nb_digit(uintmax_t nb, int base)
{
	int i;

	i = 1;
	if (base < 2 || nb == 0)
		return (0);
	while (nb >= base && i++ >= 0)
		nb /= base;
	return (i);
}

static void	ft_putnbrbase(uintmax_t n, char *base, int first, int *i)
{
	unsigned int b;

	if (first && !n)
		return ;
	b = ft_strlen(base);
	if (n < b)
	{
		ft_putchar(base[n]);
		(*i)++;
		return ;
	}
	ft_putnbrbase(n / b, base, 0, i);
	ft_putnbrbase(n % b, base, 0, i);
}

static int	ft_precision(uintmax_t nb, t_param flags, int size)
{
	int i;

	i = 0;
	if (nb == 0 && flags.precision == -1)
		write(1, "0", 1);
	if (((nb && (flags.type == 'x' || flags.type == 'X') && flags.sharp)
			|| flags.type == 'p'))
		flags.type == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	else if (flags.sharp && (flags.type == 'o' || flags.type == 'O') &&
			flags.precision <= size)
		flags.precision = size + 1;
	while (flags.precision > size + i++)
		write(1, "0", 1);
	if (flags.type == 'u' || flags.type == 'U')
		ft_putnbrbase(nb, "0123456789", 1, &i);
	else if (flags.type == 'o' || flags.type == 'O')
		ft_putnbrbase(nb, "01234567", 1, &i);
	else if (flags.type == 'x' || flags.type == 'p')
		ft_putnbrbase(nb, "0123456789abcdef", 1, &i);
	else if (flags.type == 'X')
		ft_putnbrbase(nb, "0123456789ABCDEF", 1, &i);
	else if (flags.type == 'b' || flags.type == 'B')
		ft_putnbrbase(nb, "01", 1, &i);
	return (i - 1);
}

static int	ft_length(uintmax_t nb, t_param flags, int size)
{
	int i;
	int j;
	int pre;

	i = 0;
	pre = (nb && ((flags.type == 'x' || flags.type == 'X') && flags.sharp))
			|| flags.type == 'p' ? 2 : 0;
	if ((flags.type == 'o' || flags.type == 'O') && (flags.precision > size ||
				(flags.precision == -1 && nb == 0)) && flags.sharp)
		flags.length++;
	if (flags.zero && flags.precision == -1 && !flags.minus)
		flags.precision = flags.length - pre;
	else if (flags.precision == -1)
		flags.precision = size == 0 ? size + 1 : size;
	if (flags.sharp && (flags.type == 'o' || flags.type == 'O'))
		flags.length--;
	if (!flags.minus)
		while (flags.length > flags.precision + pre + i++)
			write(1, " ", 1);
	j = ft_precision(nb, flags, size);
	if (flags.minus)
		while (flags.length > flags.precision + pre + i++)
			write(1, " ", 1);
	return (i + j + pre - 1);
}

int			ft_printu(va_list ap, t_param flags)
{
	uintmax_t	nb;
	int			size;
	int			pre;

	if (flags.flag == 'j' && flags.type != 'p')
		nb = va_arg(ap, uintmax_t);
	else if ((flags.flag == 'l' || flags.type == 'p'))
		nb = va_arg(ap, unsigned long);
	else if (flags.flag == 'L' && flags.type != 'p')
		nb = va_arg(ap, unsigned long long);
	else
		nb = flags.flag == 'z' ? va_arg(ap, size_t) : va_arg(ap, unsigned int);
	if (flags.flag == 'H' && flags.type != 'p')
		nb = (unsigned char)nb;
	else
		nb = flags.flag == 'h' && flags.type != 'p' ? (unsigned short)nb : nb;
	size = nb_digit(nb, 10);
	if (flags.type == 'o' || flags.type == 'O')
		size = nb_digit(nb, 8);
	else if (flags.type == 'X' || flags.type == 'x' || flags.type == 'p')
		size = nb_digit(nb, 16);
	flags.precision = flags.precision > size || flags.precision == -1 ?
		flags.precision : size;
	return (ft_length(nb, flags, size));
}
