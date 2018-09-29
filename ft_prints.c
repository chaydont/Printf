/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:34:28 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 14:50:43 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_prints(va_list ap, t_param flags)
{
	int		length;
	char	*str;
	int		i;

	i = 0;
	if ((str = va_arg(ap, char*)) == NULL)
		str = "(null)";
	length = ft_strlen(str);
	if (flags.precision < length && flags.precision != -1)
		length = flags.precision;
	if (!flags.minus)
		while (i++ < flags.length - length)
			flags.zero ? write(1, "0", 1) : write(1, " ", 1);
	write(1, str, length);
	if (flags.minus)
		while (i++ < flags.length - length)
			write(1, " ", 1);
	return (length > flags.length ? length : flags.length);
}
