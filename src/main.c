/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:35:27 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 17:35:39 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		print_key_inputs(void)
{
	ft_printf("<=== .OBJ SELECTION WITH NUMPAD ===>\n");
	ft_printf("0 : sqr_vt.obj\n");
	ft_printf("1 : cube_vt.obj\n");
	ft_printf("2 : 42leprechaun_vt\n");
	ft_printf("3 : teapot_v.obj\n");
	ft_printf("4 : teapot2_v.obj\n");
	ft_printf("5 : panda_vtn.obj\n");
	ft_printf("6 : grifeu_vt.obj\n");
	ft_printf("7 : orc_vt.obj\n");
	ft_printf("8 : gnome_chauve_vt.obj\n");
	ft_printf("9 : test.obj (default->empty file)\n");
	ft_printf("<=== .XPM SELECTION WITH ALPHANUMERIC ===>\n");
	ft_printf("0 : circle_weave.xpm\n");
	ft_printf("1 : redbrick.xpm\n");
	ft_printf("2 : leprechaun.xpm\n");
	ft_printf("3 : orc.xpm\n");
	ft_printf("4 : gnome_chauve.xpm\n");
}

static void		print_key_inputs_bis(void)
{
	ft_printf("<=== MOVING ==>\n");
	ft_printf("W : front\n");
	ft_printf("S : back\n");
	ft_printf("A : left\n");
	ft_printf("D : right\n");
	ft_printf("E : up\n");
	ft_printf("Q : down\n");
	ft_printf("<=== OTHER ===>\n");
	ft_printf("R : rotation on/off\n");
	ft_printf("T : texture on/off\n");
	ft_printf("ESC : leave scop\n\n");
}

static int		init(t_env *e)
{
	if (!init_glfw(e))
		return (0);
	if (!init_glad())
		return (0);
	ft_printf("OpenGL version : %s\n", glGetString(GL_VERSION));
	load_shader(e);
	load_program(e);
	glEnable(GL_DEPTH_TEST);
	init_gl_buffers(e);
	init_cam_obj_vertex_and_tex_structs(e);
	init_projection_matrix_and_uniform_att_ids(e);
	init_key_and_obj_tabs(e);
	init_xpm_name_and_tab(e);
	return (1);
}

int				main(void)
{
	t_env		e;

	if (!init(&e))
		return (0);
	ft_printf("<-------------------KEY_INPUTS------------------->\n\n");
	print_key_inputs();
	print_key_inputs_bis();
	ft_printf("<----------------------END----------------------->\n\n");
	while (!glfwWindowShouldClose(e.win))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		compute_and_send_uniform_atts_to_shaders(&e);
		glDrawElements(GL_TRIANGLES, e.gl.buf.nb_vertex, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(e.win);
		glfwPollEvents();
	}
	exit_all(&e);
	return (0);
}
