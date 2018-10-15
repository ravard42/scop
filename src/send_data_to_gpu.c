/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data_to_gpu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:43:29 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 14:17:08 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		vertex_desalloc(t_env *e)
{
	e->o.v.nb_vtnc = 0;
	if (e->o.v.vtnc)
		free(e->o.v.vtnc);
	e->o.v.vtnc = NULL;
	e->o.v.nb_elem = 0;
	if (e->o.v.elem)
		free(e->o.v.elem);
	e->o.v.elem = NULL;
}

void			send_data_to_gpu(t_env *e, int id)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * e->o.v.nb_vtnc * 10,
			e->o.v.vtnc, GL_STATIC_DRAW);
	e->gl.loc.a.pos = glGetAttribLocation(e->gl.sha.prog, "position");
	glVertexAttribPointer(e->gl.loc.a.pos, 3, GL_FLOAT, GL_FALSE,
			10 * sizeof(float), 0);
	glEnableVertexAttribArray(e->gl.loc.a.pos);
	e->gl.loc.a.tex = glGetAttribLocation(e->gl.sha.prog, "texcoord");
	if (!e->o.tex)
		gl_triangle_colors(e);
	else
		gl_texture(e);
	glEnableVertexAttribArray(e->gl.loc.a.tex);
	e->gl.buf.nb_vertex = e->o.v.nb_elem * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * e->gl.buf.nb_vertex,
			e->o.v.elem, GL_STATIC_DRAW);
	ft_printf("%s <===> number of triangles = %d\n",
			e->obj_tab[id], e->o.v.nb_elem);
	e->o.id = id;
	vertex_desalloc(e);
}
