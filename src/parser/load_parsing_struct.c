/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_parsing_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:09:19 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:03:58 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			init_f_obj_p(t_f_obj_p *o)
{
	o->vn_only = -1;
	o->nb_v = 0;
	o->v = NULL;
	o->nb_vt = 0;
	o->vt = NULL;
	o->nb_vn = 0;
	o->vn = NULL;
	o->nb_elem = 0;
	o->elem = NULL;
}

static int		handle_v_vt_vn(char **tab, int *i, t_f_obj_p *o)
{
	int		x;
	int		k;

	x = 0;
	if (!ft_strcmp("v", tab[0]))
		x = 1;
	else if (!ft_strcmp("vt", tab[0]))
		x = 2;
	else if (!ft_strcmp("vn", tab[0]))
		x = 3;
	if (x >= 1 && x <= 3 && nb_param_error(tab, x) == -1)
		return (-1);
	else if (x == 0)
		return (0);
	k = 0;
	if (x == 1)
		while (++k < 4)
			o->v[++i[0]] = atof(tab[k]);
	else if (x == 2)
		while (++k < 3)
			o->vt[++i[1]] = atof(tab[k]);
	else if (x == 3)
		while (++k < 4)
			o->vn[++i[2]] = atof(tab[k]);
	return (1);
}

static int		handle_quad(int *i, t_f_obj_p *o)
{
	int	j;

	j = -1;
	while (++j < 3)
	{
		o->elem[i[3] + 2][j] = o->elem[i[3]][j];
		o->elem[i[3] + 1][j] = o->elem[i[3] - 1][j];
		o->elem[i[3]][j] = o->elem[i[3] - 3][j];
	}
	j = -1;
	while (++j < 3)
		if (verif_vtn_in_f(o, i[3] + j) == -1)
			return (-1);
	i[3] += 2;
	return (1);
}

static int		handle_f(char **tab, int *i, int nb_vert, t_f_obj_p *o)
{
	char	**sp;
	int		k;

	if (!ft_strcmp("f", tab[0]) && nb_vert >= 3)
	{
		k = 0;
		while (++k <= nb_vert)
		{
			sp = ft_strsplit(tab[k], '/');
			if (sp[0])
				o->elem[++i[3]][0] += ft_atoi(sp[0]);
			if (sp[0] && sp[1] && !o->vn_only)
				o->elem[i[3]][1] += ft_atoi(sp[1]);
			if (sp[0] && sp[1] && (o->vn_only || sp[2]))
				o->elem[i[3]][2] += ft_atoi(sp[2 - o->vn_only]);
			free_split(sp);
			if (verif_vtn_in_f(o, i[3]) == -1)
				return (-1);
		}
		if (nb_vert == 4 && handle_quad(i, o) == -1)
			return (-1);
	}
	return (0);
}

int				fill_f_obj_p(char *str, int *i, t_f_obj_p *o)
{
	char		*tmp;
	char		**tab;
	char		k;
	char		y;

	tmp = str;
	str = ft_revstr(rm_begin_whitespace(ft_revstr(rm_begin_whitespace(str))));
	str = rm_multi_whitespace(str);
	if (str[0] == '\0' && free_ok(tmp))
		return (0);
	tab = ft_strsplit(str, ' ');
	free(tmp);
	k = -1;
	while (tab[(size_t)++k])
		;
	y = handle_v_vt_vn(tab, i, o);
	if (y == -1 && parsing_desalloc(o) && free_split(tab))
		return (-1);
	if (y == 0)
		if (handle_f(tab, i, k - 1, o) == -1 && parsing_desalloc(o)
				&& free_split(tab))
			return (-1);
	free_split(tab);
	return (0);
}
