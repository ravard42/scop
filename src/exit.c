/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 22:05:47 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 12:28:42 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				tex_desalloc(t_env *e)
{
	e->o.t.nb_pix = 0;
	if (e->o.t.pix)
		free(e->o.t.pix);
	e->o.t.pix = NULL;
}

void				exit_all(t_env *e)
{
	tex_desalloc(e);
	glDeleteProgram(e->gl.sha.prog);
	glDeleteShader(e->gl.sha.vert);
	glDeleteShader(e->gl.sha.frag);
	glDeleteBuffers(1, &e->gl.buf.ebo);
	glDeleteBuffers(1, &e->gl.buf.vbo);
	glDeleteVertexArrays(1, &e->gl.buf.vao);
	glfwTerminate();
	ft_printf("Good bye\n");
	exit(0);
}
