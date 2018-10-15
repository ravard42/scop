/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 22:08:36 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:04:02 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		verif_f(char *tab, t_f_obj_p *o)
{
	int		i;
	int		k;
	char	**sp;

	if (vn_only_error(tab, o))
		return (-1);
	sp = ft_strsplit(tab, '/');
	i = -1;
	while (sp[++i])
	{
		if (sp[i][0] == '0' && !sp[i][1]
				&& free_split(sp))
			return (-2);
		k = -1;
		while (sp[i][++k])
			if (!(sp[i][k] >= '0' && sp[i][k] <= '9')
					&& free_split(sp))
				return (-3);
	}
	free_split(sp);
	return (1);
}

int		verif_vtn_in_f(t_f_obj_p *o, int i)
{
	if (o->elem[i][0] >= o->nb_v
			|| o->elem[i][1] >= o->nb_vt
			|| o->elem[i][2] >= o->nb_vn)
	{
		ft_printf("indice de vertex incorrect\n");
		return (-1);
	}
	return (1);
}
