/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 22:00:50 by ravard            #+#    #+#             */
/*   Updated: 2018/08/21 22:03:31 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				gl_triangle_colors(t_env *e)
{
	static float color_tab[] = {0.6f, 0.6f, 0.6f, 0.8f, 0.8f, 0.8f,
							0.2f, 0.2f, 0.2f, 0.4f, 0.4f, 0.4f};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB,
			GL_FLOAT, color_tab);
	glVertexAttribPointer(e->gl.loc.a.tex, 2, GL_FLOAT, GL_FALSE,
			10 * sizeof(float), (void *)(8 * sizeof(float)));
}

void				gl_texture(t_env *e)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, e->o.t.nb_pix, e->o.t.nb_pix, 0,
			GL_RGB, GL_FLOAT, e->o.t.pix);
	glVertexAttribPointer(e->gl.loc.a.tex, 2, GL_FLOAT, GL_FALSE,
			10 * sizeof(float), (void *)(3 * sizeof(float)));
}
