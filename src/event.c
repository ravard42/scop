/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:32:30 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 16:34:44 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
		if (key == 48 + i
				&& (!e->o.tex || !(e->o.transi = 0.0f))
				&& tex_desalloc(e))
			load_sqr_xpm(i, e->xpm_tab[i], e);
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
	glfwSetKeyCallback(e->win, key_callback);
}
