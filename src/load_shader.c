/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:34:09 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 17:24:59 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char		*load_source(char *path)
{
	int		fd;
	int		size[2];
	char	tmp[50];
	char	*source;

	fd = open(path, O_RDONLY);
	size[0] = 0;
	while ((size[1] = read(fd, tmp, 50)))
		size[0] += size[1];
	close(fd);
	source = (char *)malloc(sizeof(char) * size[0] + 1);
	fd = open(path, O_RDONLY);
	read(fd, source, size[0]);
	close(fd);
	source[size[0]] = '\0';
	return (source);
}

static void		compil_glsl_debug(GLint status, char c, t_env *e)
{
	GLchar		infolog[1024];

	if (c == 'v')
	{
		if (status)
			ft_printf("\ncompilation vertex shader OK\n");
		else
		{
			glGetShaderInfoLog(e->gl.sha.vert, sizeof(infolog), NULL, infolog);
			ft_printf("\nError compiling vertex shader : '%s'\n", infolog);
		}
	}
	else if (c == 'f')
	{
		if (status)
			ft_printf("compilation fragment shader OK\n");
		else
		{
			glGetShaderInfoLog(e->gl.sha.frag, sizeof(infolog), NULL, infolog);
			ft_printf("Error compiling fragment shader : '%s'\n", infolog);
		}
	}
}

void			load_shader(t_env *e)
{
	char		*shader_source;
	GLint		status;

	e->gl.sha.vert = glCreateShader(GL_VERTEX_SHADER);
	shader_source = load_source(VERTEX);
	glShaderSource(e->gl.sha.vert, 1,
			(const GLchar *const *)&shader_source, NULL);
	free(shader_source);
	glCompileShader(e->gl.sha.vert);
	glGetShaderiv(e->gl.sha.vert, GL_COMPILE_STATUS, &status);
	compil_glsl_debug(status, 'v', e);
	e->gl.sha.frag = glCreateShader(GL_FRAGMENT_SHADER);
	shader_source = load_source(FRAGMENT);
	glShaderSource(e->gl.sha.frag, 1,
			(const GLchar *const *)&shader_source, NULL);
	free(shader_source);
	glCompileShader(e->gl.sha.frag);
	glGetShaderiv(e->gl.sha.frag, GL_COMPILE_STATUS, &status);
	compil_glsl_debug(status, 'f', e);
}

void			load_program(t_env *e)
{
	GLint		status;
	GLchar		infolog[1024];

	e->gl.sha.prog = glCreateProgram();
	glAttachShader(e->gl.sha.prog, e->gl.sha.vert);
	glAttachShader(e->gl.sha.prog, e->gl.sha.frag);
	glLinkProgram(e->gl.sha.prog);
	glGetProgramiv(e->gl.sha.prog, GL_LINK_STATUS, &status);
	if (status)
		ft_printf("compilation program shader OK\n\n");
	else
	{
		glGetProgramInfoLog(e->gl.sha.prog, sizeof(infolog), NULL, infolog);
		ft_printf("Error compiling program shader : '%s'\n\n", infolog);
	}
	glUseProgram(e->gl.sha.prog);
}
