/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:09:38 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 17:07:06 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_flag(char flag, char *str)
{
	char *size;
	char c;

	size = "HhlLjz";
	if ((*str == 'h' || *str == 'l') && str[0] == str[1])
		c = *str + 'A' - 'a';
	else
		c = *str;
	if (flag && ft_strchr(size, c) <= ft_strchr(size, flag))
		return (flag);
	return (c);
}

static void	ft_flag2(char c, t_param *flags)
{
	if (c == '#')
		flags->sharp = 1;
	else if (c == '+')
		flags->plus = 1;
	else if (c == '-')
		flags->minus = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == '0')
		flags->zero = 1;
}

static void	init_param(t_param *flags)
{
	flags->sharp = 0;
	flags->plus = 0;
	flags->minus = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->length = -1;
	flags->precision = -1;
	flags->flag = '\0';
	flags->type = '\0';
}

static void	other(t_param *flags)
{
	if (flags->type != '\0' && ft_strchr("DUOCS", flags->type))
	{
		flags->type += 32;
		flags->flag = 'l';
	}
}

int			parsing(char *str, t_param *flags)
{
	int		i;

	init_param(flags);
	i = 0;
	while (ft_strchr("hjlz+- .#0123465789", str[i]) && str[i])
	{
		if (ft_strchr("hljz", str[i]))
			flags->flag = ft_flag(flags->flag, str + i);
		if ((str[i] == 'h' || str[i] == 'l') && str[i] == str[i + 1])
			i++;
		else if (ft_strchr("#+-0 ", str[i]))
			ft_flag2(str[i], flags);
		else if (ft_isdigit(str[i]) && str[i] != '0')
			i += ft_nb_digit_base(-(flags->length = ft_atoi(str + i)), 10) - 1;
		else if (str[i] == '.' && !ft_isdigit(str[i + 1]))
			flags->precision = 0;
		else if (str[i] == '.')
			i += ft_nb_digit_base(-(flags->precision = ft_atoi(str + i + 1))
					, 10);
		i++;
	}
	flags->type = str[i];
	other(flags);
	return (flags->type == '\0' ? i - 1 : i);
}
