/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 22:08:03 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 15:39:13 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		ft_hex_atoi(char *str)
{
	int		i;
	int		ret;
	char	up;

	i = -1;
	ret = 0;
	while (++i < 6)
	{
		up = ft_toupper(str[i]);
		if (up >= 'A' && up <= 'F')
			ret += (10 + up - 'A') * ft_power(16, i);
		else
			ret += (up - '0') * ft_power(16, i);
	}
	return (ret);
}

static void		load_xpm_bijection(char **xpm, t_f_xpm_p *x)
{
	int		i;
	char	**split;
	char	*rev;
	char	excex;

	x->ascii = (char **)malloc(sizeof(char *) * (x->ncolors + 1));
	i = -1;
	while (++i < x->ncolors)
		x->ascii[i] = (char *)malloc(sizeof(char) * (x->chars_per_pixel + 1));
	x->ascii[i] = NULL;
	x->hexa = (int *)malloc(sizeof(int) * x->ncolors);
	i = -1;
	while (++i < x->ncolors)
	{
		ft_strncpy(x->ascii[i], xpm[i + 1], x->chars_per_pixel);
		x->ascii[i][x->chars_per_pixel] = '\0';
		split = ft_strsplit(xpm[i + 1], ' ');
		excex = (split[2] == NULL) ? 1 : 0;
		rev = ft_revstr(split[2 - excex]);
		x->hexa[i] = ft_hex_atoi(rev);
		free_split(split);
	}
}

static void		init_texture_structs(char **xpm, t_f_xpm_p *x, t_env *e)
{
	char			**split;
	int				i;

	split = ft_strsplit(xpm[0], ' ');
	x->size = ft_atoi(split[0]);
	x->ncolors = ft_atoi(split[2]);
	x->chars_per_pixel = ft_atoi(split[3]);
	free_split(split);
	load_xpm_bijection(xpm, x);
	x->data_line = (char *)malloc(sizeof(char) *
			(x->size * x->size * x->chars_per_pixel + 1));
	x->data_line[0] = '\0';
	i = 0;
	while (++i <= x->size)
		ft_strcat(x->data_line, xpm[x->ncolors + i]);
	e->o.t.nb_pix = x->size;
	e->o.t.pix = (float *)malloc(sizeof(float) * x->size * x->size * 3);
}

static void		free_xpm_struct(t_f_xpm_p *x)
{
	free_split(x->ascii);
	free(x->hexa);
	free(x->data_line);
}

void			load_sqr_xpm(char **xpm, t_env *e)
{
	t_f_xpm_p		x;
	int				var[3];

	tex_desalloc(e);
	init_texture_structs(xpm, &x, e);
	var[0] = -1;
	while (++var[0] < x.size * x.size)
	{
		var[1] = -1;
		while (++var[1] < x.ncolors)
		{
			if (!ft_strncmp(x.data_line + var[0] * x.chars_per_pixel,
						x.ascii[var[1]], x.chars_per_pixel))
			{
				var[2] = x.hexa[var[1]];
				break ;
			}
		}
		e->o.t.pix[var[0] * 3] = ((var[2] & 0xff0000) >> 16) / (float)256;
		e->o.t.pix[var[0] * 3 + 1] = ((var[2] & 0xff00) >> 8) / (float)256;
		e->o.t.pix[var[0] * 3 + 2] = (var[2] & 0xff) / (float)256;
	}
	if ((e->xpm_tab[5] = xpm) && e->o.tex)
		gl_texture(e);
	free_xpm_struct(&x);
}
