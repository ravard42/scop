/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:33:33 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:39:03 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		init_glfw(t_env *e)
{
	if (!glfwInit())
	{
		ft_printf("an error occured in init_glfw()...\n");
		return (0);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (!(e->win = glfwCreateWindow(WINX, WINY, "Scop", NULL, NULL)))
	{
		ft_printf("an error occured in glfwCreateWindow()...\n");
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(e->win);
	glfwSetWindowUserPointer(e->win, e);
	set_callback(e);
	return (1);
}

int		init_glad(void)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ft_printf("an error occured in init_glad() ...\n");
		glfwTerminate();
		return (0);
	}
	return (1);
}

void	init_projection_matrix_and_uniform_att_ids(t_env *e)
{
	float ar;
	float fov;
	float znear;
	float zfar;

	ar = (float)WINX / WINY;
	fov = 2 * M_PI * 7 / 36;
	znear = -0.1;
	zfar = -100.0;
	cpy_m(e->proj_m, NULL);
	e->proj_m[0][0] = 1 / (ar * tan(fov / 2));
	e->proj_m[1][1] = 1 / tan(fov / 2);
	e->proj_m[2][2] = (znear + zfar) / (znear - zfar);
	e->proj_m[2][3] = -2 * znear * zfar / (znear - zfar);
	e->proj_m[3][2] = -1;
	e->gl.loc.u.transfo = glGetUniformLocation(e->gl.sha.prog, "transfo");
	e->gl.loc.u.transi = glGetUniformLocation(e->gl.sha.prog, "transi");
	if (e->gl.loc.u.transfo == 0xFFFFFFFF || e->gl.loc.u.transi == 0xFFFFFFF)
		ft_printf("init_uniform_var error\n");
}

void	init_gl_buffers(t_env *e)
{
	glGenVertexArrays(1, &e->gl.buf.vao);
	glBindVertexArray(e->gl.buf.vao);
	glGenBuffers(1, &e->gl.buf.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, e->gl.buf.vbo);
	e->gl.buf.nb_vertex = 0;
	glGenBuffers(1, &e->gl.buf.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->gl.buf.ebo);
	glGenTextures(1, &e->gl.buf.tex);
	glBindTexture(GL_TEXTURE_2D, e->gl.buf.tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void	init_cam_obj_vertex_and_tex_structs(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 2)
		e->c.pos[i] = 0;
	e->c.pos[2] = 5;
	e->c.mouv = 0;
	e->o.id = -1;
	e->o.rot = 0;
	e->o.angle_rot = 0;
	e->o.tex = 0;
	e->o.transi = 0.0f;
	e->o.v.nb_vtnc = 0;
	e->o.v.vtnc = NULL;
	e->o.v.nb_elem = 0;
	e->o.v.elem = NULL;
	e->o.t.nb_pix = 0;
	e->o.t.pix = NULL;
}
