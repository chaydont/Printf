/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:51:49 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 19:34:35 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		functions(va_list ap, t_param flags)
{
	char	c;
	int		i;

	i = 0;
	if (flags.type == '\0')
		return (0);
	else if (ft_strchr("dDi", flags.type))
		return (ft_printi(ap, flags));
	else if (flags.type == 's')
		return (ft_prints(ap, flags));
	else if (ft_strchr("oxXup", flags.type))
		return (ft_printu(ap, flags));
	else if (flags.type == 'c')
		return (ft_printc(ap, flags));
	c = flags.type;
	if (!flags.minus)
		while (i++ < flags.length - 1)
			flags.zero ? write(1, "0", 1) : write(1, " ", 1);
	ft_putchar(c);
	if (flags.minus)
		while (i++ < flags.length - 1)
			write(1, " ", 1);
	return (i);
}

int		ft_printf(const char *restrict str, ...)
{
	va_list ap;
	char	*print;
	int		i;
	int		j;
	t_param flags;

	i = 0;
	j = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i += parsing((char*)str + i + 1, &flags) + 1;
			j += functions(ap, flags) - 1;
		}
		else
			ft_putchar(str[i]);
		i++;
		j++;
	}
	return (j);
}
