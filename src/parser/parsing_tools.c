/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:44:50 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 14:05:48 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				f_triangle_number(char *str, t_f_obj_p *o)
{
	int		i;
	char	**tab;
	char	err;

	tab = ft_strsplit(str, ' ');
	i = -1;
	while (tab[++i])
		if ((err = verif_f(tab[i], o)) < 0
				&& free_split(tab))
			return (err);
	free_split(tab);
	i -= 2;
	if (i < 1)
		return (-4);
	return (i);
}

static int		check_line(char *str, t_f_obj_p *o)
{
	int		nb_tri;

	if (!ft_strncmp("v ", str, 2))
		o->nb_v++;
	else if (!ft_strncmp("vt", str, 2))
		o->nb_vt++;
	else if (!ft_strncmp("vn", str, 2))
		o->nb_vn++;
	else if (!ft_strncmp("f ", str, 2))
	{
		nb_tri = f_triangle_number(str + 2, o);
		if (invalid_face_error_msg(nb_tri))
			return (-1);
		o->nb_elem += nb_tri;
	}
	return (0);
}

int				recup_size(int fd, t_f_obj_p *o)
{
	int		i;
	char	*str;
	char	*tmp;

	o->vn_only = -1;
	i = -1;
	while (get_next_line(fd, &str))
	{
		tmp = str;
		str = ft_revstr(rm_begin_whitespace(
					ft_revstr(rm_begin_whitespace(str))));
		str = rm_multi_whitespace(str);
		i++;
		if (check_line(str, o) == -1
				&& free_ok(tmp))
			return (-1);
		free(tmp);
	}
	return (0);
}

void			parsing_alloc(t_f_obj_p *o)
{
	int	i;
	int	j;

	o->v = (float *)malloc(sizeof(float) * o->nb_v * 3);
	o->vt = (float *)malloc(sizeof(float) * o->nb_vt * 2);
	o->vn = (float *)malloc(sizeof(float) * o->nb_vn * 3);
	o->elem = (int **)malloc(sizeof(int *) * o->nb_elem * 3);
	i = -1;
	while (++i < o->nb_elem * 3)
		o->elem[i] = (int *)malloc(sizeof(int) * 4);
	i = -1;
	j = 0;
	while (++i < o->nb_elem * 3)
	{
		o->elem[i][0] = -1;
		o->elem[i][1] = -1;
		o->elem[i][2] = -1;
		o->elem[i][3] = j;
		j = (i % 3 == 2) ? j + 1 : j;
		j %= 4;
	}
}

int				parsing_desalloc(t_f_obj_p *o)
{
	int	i;

	if (o->v && free_ok(o->v))
		o->v = NULL;
	if (o->vt && free_ok(o->vt))
		o->vt = NULL;
	if (o->vn && free_ok(o->vn))
		o->vn = NULL;
	if (o->elem)
	{
		i = -1;
		while (++i < o->nb_elem * 3)
			free(o->elem[i]);
		free(o->elem);
		o->elem = NULL;
	}
	return (1);
}
