/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:13:50 by chaydont          #+#    #+#             */
/*   Updated: 2017/12/13 14:51:10 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_param
{
	int		sharp;
	int		plus;
	int		minus;
	int		zero;
	int		space;

	int		length;
	int		precision;

	char	flag;
	char	type;
}				t_param;

int				ft_printf(const char *str, ...);
int				parsing(char *str, t_param *flags);
int				ft_printu(va_list ap, t_param flags);
int				ft_printi(va_list ap, t_param flags);
int				ft_prints(va_list ap, t_param flags);
int				ft_printc(va_list ap, t_param flags);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
void			ft_putchar(char c);
int				ft_nb_digit_base(int n, int base);
int				ft_isdigit(int c);

#endif
