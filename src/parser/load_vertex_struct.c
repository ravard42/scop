/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:16:42 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:43:07 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int				first_occurrence(t_f_obj_p *o, int i, int *k, t_env *e)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (o->elem[j][0] == o->elem[i][0] &&
				o->elem[j][1] == o->elem[i][1] &&
				o->elem[j][2] == o->elem[i][2] &&
				o->elem[j][3] == o->elem[i][3])
		{
			(*k)++;
			return (e->o.v.elem[j]);
		}
	}
	return (i - *k);
}

static int				elem_id_max(t_env *e)
{
	int					max;
	int					i;

	max = 0;
	i = -1;
	while (++i < e->o.v.nb_elem * 3)
		if (e->o.v.elem[i] > max)
			max = e->o.v.elem[i];
	return (max);
}

static void				load_e_d_elem(t_f_obj_p *o, t_env *e)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < e->o.v.nb_elem * 3)
		e->o.v.elem[i] = first_occurrence(o, i, &k, e);
}

static void				cp_vtnc(t_f_obj_p *o, int k, int i, t_env *e)
{
	int		j;
	float	uvcol[8];

	j = -1;
	while (++j < 8)
		uvcol[j] = 0.0;
	uvcol[2] = 1.0;
	uvcol[5] = 1.0;
	uvcol[6] = 1.0;
	uvcol[7] = 1.0;
	j = -1;
	while (++j < 3)
	{
		e->o.v.vtnc[10 * k + j] = o->v[o->elem[i][0] * 3 + j];
		if (j < 2)
		{
			e->o.v.vtnc[10 * k + 3 + j] = (o->elem[i][1] != -1) ?
				o->vt[o->elem[i][1] * 2 + j] : 0.0;
			e->o.v.vtnc[10 * k + 8 + j] = uvcol[o->elem[i][3] * 2 + j];
		}
		e->o.v.vtnc[10 * k + 5 + j] = (o->elem[i][2] != -1) ?
			o->vn[o->elem[i][2] * 3 + j] : 0.0;
	}
}

void					fill_vertex_struct(t_f_obj_p *o, t_env *e)
{
	int						id_vtnc;
	int						i;

	e->o.v.nb_elem = o->nb_elem;
	e->o.v.elem = (GLint *)malloc(sizeof(GLint) * e->o.v.nb_elem * 3);
	load_e_d_elem(o, e);
	e->o.v.nb_vtnc = elem_id_max(e) + 1;
	e->o.v.vtnc = (GLfloat *)malloc(sizeof(GLfloat) * e->o.v.nb_vtnc * 10);
	cp_vtnc(o, 0, 0, e);
	id_vtnc = 1;
	i = 0;
	while (id_vtnc < e->o.v.nb_vtnc)
	{
		if (e->o.v.elem[i] == id_vtnc)
		{
			cp_vtnc(o, id_vtnc, i, e);
			id_vtnc++;
		}
		i++;
	}
}
