/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:34:18 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 13:51:43 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			load_f_obj_data(char id, t_env *e)
{
	t_f_obj_p	o;
	int			fd;
	char		*str;
	int			i[5];

	init_f_obj_p(&o);
	fd = open(e->obj_tab[(size_t)id], O_RDONLY);
	if ((fd == -1 && ft_printf("file.obj loading error, open return -1\n"))
			|| recup_size(fd, &o) == -1)
		return (0);
	close(fd);
	parsing_alloc(&o);
	fd = open(e->obj_tab[(size_t)id], O_RDONLY);
	i[4] = -1;
	while (++i[4] < 4)
		i[i[4]] = -1;
	while (get_next_line(fd, &str))
		if (fill_f_obj_p(str, i, &o) == -1)
			return (0);
	close(fd);
	if (o.nb_elem)
		fill_vertex_struct(&o, e);
	parsing_desalloc(&o);
	return (1);
}
