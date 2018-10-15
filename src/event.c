/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:32:30 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 15:39:12 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		init_key_obj_xpm_tabs(t_env *e)
{
	e->key_tab[0] = D;
	e->key_tab[1] = A;
	e->key_tab[2] = E;
	e->key_tab[3] = Q;
	e->key_tab[4] = W;
	e->key_tab[5] = S;
	e->obj_tab[0] = "./f_obj/sqr_vt.obj";
	e->obj_tab[1] = "./f_obj/cube_vt.obj";
	e->obj_tab[2] = "./f_obj/42leprechaun_vt.obj";
	e->obj_tab[3] = "./f_obj/teapot_v.obj";
	e->obj_tab[4] = "./f_obj/teapot2_v.obj";
	e->obj_tab[5] = "./f_obj/panda_vtn.obj";
	e->obj_tab[6] = "./f_obj/grifeu_vt.obj";
	e->obj_tab[7] = "./f_obj/orc_vt.obj";
	e->obj_tab[8] = "./f_obj/gnome_chauve_vt.obj";
	e->obj_tab[9] = "./f_obj/test.obj";
	e->xpm_tab[0] = circle_weave_xpm;
	e->xpm_tab[1] = redbrick_xpm;
	e->xpm_tab[2] = leprechaun_xpm;
	e->xpm_tab[3] = orc_xpm;
	e->xpm_tab[4] = gnome_chauve_xpm;
	e->xpm_tab[5] = NULL;
}

static void		texture(t_env *e)
{
	e->o.tex = (e->o.tex) ? 0 : 1;
	e->o.transi = 0.0f;
	if (e->o.tex && e->xpm_tab[5])
		gl_texture(e);
	else
		gl_triangle_colors(e);
}

static void		key_press(GLFWwindow *window, int key, t_env *e)
{
	int		i;

	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (key == T && e->xpm_tab[5])
		texture(e);
	else if (key == R)
		e->o.rot = (e->o.rot == 0) ? 1 : 0;
	i = -1;
	while (++i < 6)
		if (key == e->key_tab[i])
			e->c.mouv |= ft_power(2, i);
	i = -1;
	while (++i < NB_OBJ)
		if (key == 320 + i
				&& load_f_obj_data(i, e)
				&& !(e->o.transi = 0.0f))
			send_data_to_gpu(e, i);
	i = -1;
	while (++i < NB_XPM)
		if (key == 48 + i && !(e->o.transi = 0.0f))
			load_sqr_xpm(e->xpm_tab[i], e);
}

static void		key_callback(GLFWwindow *window, int key,
		int scancode, int action, int mods)
{
	t_env	*e;
	int		i;

	(void)scancode;
	(void)mods;
	e = glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS)
		key_press(window, key, e);
	else if (action == GLFW_RELEASE)
	{
		i = -1;
		while (++i < 6)
			if (key == e->key_tab[i])
				e->c.mouv &= ~ft_power(2, i);
	}
}

void			set_callback(t_env *e)
{
	init_key_obj_xpm_tabs(e);
	glfwSetKeyCallback(e->win, key_callback);
}
