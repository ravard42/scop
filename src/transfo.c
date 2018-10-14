/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:21:21 by ravard            #+#    #+#             */
/*   Updated: 2018/10/13 07:26:36 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			cpy_m(float dst[4][4], float src[4][4])
{
	int		i[2];

	i[0] = -1;
	while (++i[0] < 4)
	{
		i[1] = -1;
		while (++i[1] < 4)
			dst[i[0]][i[1]] = (src) ? src[i[0]][i[1]] : 0.0f;
	}
}

static void		translate(t_env *e)
{
	cpy_m(e->c.tra_m, NULL);
	e->c.tra_m[0][0] = 1;
	e->c.tra_m[0][3] = -e->c.pos[0];
	e->c.tra_m[1][1] = 1;
	e->c.tra_m[1][3] = -e->c.pos[1];
	e->c.tra_m[2][2] = 1;
	e->c.tra_m[2][3] = -e->c.pos[2];
	e->c.tra_m[3][3] = 1;
}

static void		rotate(t_env *e)
{
	float	rot;

	cpy_m(e->o.rot_m, NULL);
	rot = ((float)e->o.angle_rot / 256) * 2 * M_PI;
	e->o.rot_m[0][0] = cos(rot);
	e->o.rot_m[0][2] = sin(rot);
	e->o.rot_m[1][1] = 1;
	e->o.rot_m[2][0] = -sin(rot);
	e->o.rot_m[2][2] = cos(rot);
	e->o.rot_m[3][3] = 1;
	if (e->o.rot)
	{
		e->o.angle_rot++;
		e->o.angle_rot %= 256;
	}
}

static void		produit_m(float dst[4][4], float src[4][4])
{
	float		tmp[4][4];
	int			i[2];
	int			k;

	cpy_m(tmp, dst);
	cpy_m(dst, NULL);
	i[0] = -1;
	while (++i[0] < 4)
	{
		i[1] = -1;
		while (++i[1] < 4)
		{
			k = -1;
			while (++k < 4)
				dst[i[0]][i[1]] += tmp[i[0]][k] * src[k][i[1]];
		}
	}
}

void			compute_and_send_uniform_atts_to_shaders(t_env *e)
{
	float	line_up_m[4][4];

	mouv_cam(e);
	translate(e);
	rotate(e);
	cpy_m(e->transfo_m, e->proj_m);
	produit_m(e->transfo_m, e->c.tra_m);
	produit_m(e->transfo_m, e->o.rot_m);
	if (e->o.id == 2 || e->o.id == 3 || e->o.id == 5)
	{
		cpy_m(line_up_m, e->c.tra_m);
		line_up_m[0][3] = 0;
		line_up_m[1][3] = (e->o.id != 2) ? -1.25 : 0;
		line_up_m[2][3] = (e->o.id == 2) ? -1.4403585 : 0;
		produit_m(e->transfo_m, line_up_m);
	}
	glUniformMatrix4fv(e->gl.loc.u.transfo, 1, GL_TRUE, &e->transfo_m[0][0]);
	e->o.transi = (e->o.transi >= 1) ? 1 : e->o.transi + 0.005;
	glUniform1f(e->gl.loc.u.transi, e->o.transi);
}
