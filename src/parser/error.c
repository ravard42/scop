/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 07:43:27 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:52:02 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		sl_cpt(char *str)
{
	int		cpt;
	int		i;

	cpt = 0;
	i = -1;
	while (str[++i] && cpt < 2)
		cpt = (str[i] == '/') ? cpt + 1 : cpt;
	return (cpt);
}

int				vn_only_error(char *tab, t_f_obj_p *o)
{
	char	**sp;
	int		i;
	char	tmp;
	char	ret;

	sp = ft_strsplit(tab, ' ');
	i = -1;
	while (sp[++i])
	{
		tmp = o->vn_only;
		o->vn_only = (sl_cpt(sp[i]) == 2
					&& ft_strchr(ft_strchr(sp[i], '/') + 1, '/')
					== ft_strchr(sp[i], '/') + 1) ? 1 : 0;
		ret = (tmp == -1 || tmp == o->vn_only) ? 0 : 1;
	}
	free_split(sp);
	return (ret);
}

int				nb_param_error(char **tab, int x)
{
	int		i;
	int		k;

	i = (x == 1 || x == 3) ? 3 : 2;
	k = -1;
	while (tab[++k])
		;
	k--;
	if (k < i)
	{
		ft_printf("error : wrong number of coordinate somewhere\n");
		return (-1);
	}
	return (0);
}

int				invalid_face_error_msg(int nb_tri)
{
	int		i;

	i = nb_tri;
	if (i == -1 &&
			ft_printf("be coherent : a/b/c or a//b!\n"))
		return (1);
	if (i == -2 &&
			ft_printf("Wavefront .obj : l'indexation des vertex débute å 1\n"))
		return (1);
	if (i == -3 &&
			ft_printf("Wavefront .obj : only integer in face line\n"))
		return (1);
	if (i == -4 &&
			ft_printf("Wavefront .obj : a face have at least 3 vertices\n"))
		return (1);
	if (!(i == 1 || i == 2) &&
			ft_printf("parser only accepts triangles and quads\n"))
		return (1);
	return (0);
}
