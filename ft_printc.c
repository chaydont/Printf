/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:35:44 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 15:13:43 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printc(va_list ap, t_param flags)
{
	char	c;
	int		i;

	i = 0;
	c = va_arg(ap, int);
	if (!flags.minus)
		while (i++ < flags.length - 1)
		{
			if (flags.zero)
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
	ft_putchar(c);
	if (flags.minus)
		while (i++ < flags.length - 1)
			write(1, " ", 1);
	return (i);
}
