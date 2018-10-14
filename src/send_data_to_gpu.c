/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data_to_gpu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:43:29 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 07:38:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		data_desalloc(t_env *e)
{
	e->o.d.nb_vtnc = 0;
	if (e->o.d.vtnc)
		free(e->o.d.vtnc);
	e->o.d.vtnc = NULL;
	e->o.d.nb_elem = 0;
	if (e->o.d.elem)
		free(e->o.d.elem);
	e->o.d.elem = NULL;
}

void		send_data_to_gpu(t_env *e, int id)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * e->o.d.nb_vtnc * 10,
			e->o.d.vtnc, GL_STATIC_DRAW);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * e->o.d.nb_elem * 3,
			e->o.d.elem, GL_STATIC_DRAW);
	e->gl.buf.nb_vertex = e->o.d.nb_elem * 3;
	data_desalloc(e);
	e->o.id = id;
}
