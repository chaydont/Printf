/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:15:42 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 14:35:20 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int neg;
	int i;
	int total;

	neg = 1;
	i = 0;
	total = 0;
	while (!ft_isdigit(*str) && *str != '+' && *str != '-')
	{
		if (*str != ' ' && (*str > 13 || *str < 7))
			return (0);
		str++;
	}
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		neg = -1;
	}
	while (ft_isdigit(str[i]))
		total = total * 10 + str[i++] - '0';
	return (total * neg);
}
