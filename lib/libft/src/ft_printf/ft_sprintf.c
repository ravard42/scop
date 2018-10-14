/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 22:55:22 by ravard            #+#    #+#             */
/*   Updated: 2018/03/05 23:14:43 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sprintf(char *str, const char *format, ...)
{
	static t_conv const	tab[] = {{"c", &c_conv},
								{"s", &s_conv},
								{"di", &d_conv},
								{"ouxX", &oux_conv},
								{"b", &bin_conv},
								{"", &undefined_conv}};
	va_list				va;
	int					ret;

	va_start(va, format);
	ret = conv(str, format, &va, tab);
	va_end(va);
	return (ret);
}
