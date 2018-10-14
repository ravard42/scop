/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:35:27 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 16:31:53 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			init(t_env *e)
{
	if (!init_glfw(e))
		return (0);
	if (!init_glad())
		return (0);
	glEnable(GL_DEPTH_TEST);
	load_shader(e);
	load_program(e);
	init_projection_matrix_and_uniform_att_ids(e);
	init_gl_buffers(e);
	init_cam_obj_data_tex_structs(e);
	set_callback(e);
	return (1);
}

int			main(void)
{
	t_env		e;

	if (!init(&e))
		return (0);
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
