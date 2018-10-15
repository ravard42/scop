/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:16:18 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 17:35:42 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		init_key_and_obj_tabs(t_env *e)
{
	e->key_tab[0] = D;
	e->key_tab[1] = A;
	e->key_tab[2] = E;
	e->key_tab[3] = Q;
	e->key_tab[4] = W;
	e->key_tab[5] = S;
	e->obj_tab[0] = "f_obj/sqr_vt.obj";
	e->obj_tab[1] = "f_obj/cube_vt.obj";
	e->obj_tab[2] = "f_obj/42leprechaun_vt.obj";
	e->obj_tab[3] = "f_obj/teapot_v.obj";
	e->obj_tab[4] = "f_obj/teapot2_v.obj";
	e->obj_tab[5] = "f_obj/panda_vtn.obj";
	e->obj_tab[6] = "f_obj/grifeu_vt.obj";
	e->obj_tab[7] = "f_obj/orc_vt.obj";
	e->obj_tab[8] = "f_obj/gnome_chauve_vt.obj";
	e->obj_tab[9] = "f_obj/test.obj";
}

void		init_xpm_name_and_tab(t_env *e)
{
	e->xpm_name[0] = "circle_weave.xpm";
	e->xpm_name[1] = "redbrick.xpm";
	e->xpm_name[2] = "leprechaun.xpm";
	e->xpm_name[3] = "orc.xpm";
	e->xpm_name[4] = "gnome_chauve.xpm";
	e->xpm_tab[0] = circle_weave_xpm;
	e->xpm_tab[1] = redbrick_xpm;
	e->xpm_tab[2] = leprechaun_xpm;
	e->xpm_tab[3] = orc_xpm;
	e->xpm_tab[4] = gnome_chauve_xpm;
	e->xpm_tab[5] = NULL;
}
