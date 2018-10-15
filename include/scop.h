/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:38:45 by ravard            #+#    #+#             */
/*   Updated: 2018/10/15 14:00:57 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

# include "glad.h"
# include "glfw3.h"

# define WINX 800
# define WINY 640
# define VERTEX "./shader/vertex_shader.glsl"
# define FRAGMENT "./shader/fragment_shader.glsl"

# define D 68
# define A 65
# define E 69
# define Q 81
# define W 87
# define S 83
# define R 82
# define T 84

# define NB_OBJ 10
# define NB_XPM 5

# include "circle_weave.xpm"
# include "redbrick.xpm"
# include "leprechaun.xpm"
# include "orc.xpm"
# include "gnome_chauve.xpm"

/*
** I - STRUCTS
*/

/*
** a - parsing structs
*/

typedef struct			s_f_obj_p
{
	char				vn_only;
	int					nb_v;
	float				*v;
	int					nb_vt;
	float				*vt;
	int					nb_vn;
	float				*vn;
	int					nb_elem;
	int					**elem;

}						t_f_obj_p;

typedef struct			s_f_xpm_p
{
	int					size;
	int					ncolors;
	int					chars_per_pixel;
	char				**ascii;
	int					*hexa;
	char				*data_line;
}						t_f_xpm_p;

/*
** b - file.obj and file.xpm data structs to send to GPU
*/

typedef struct			s_vertex
{
	int					nb_vtnc;
	GLfloat				*vtnc;
	int					nb_elem;
	GLint				*elem;
}						t_vertex;

typedef struct			s_tex
{
	int					nb_pix;
	GLfloat				*pix;
}						t_tex;

/*
**  c - Camera and objects
*/

typedef struct			s_cam
{
	float				pos[3];
	char				mouv;
	float				tra_m[4][4];
}						t_cam;

typedef struct			s_obj
{
	char				id;
	t_vertex			v;
	t_tex				t;
	char				rot;
	char				angle_rot;
	float				rot_m[4][4];
	char				tex;
	GLfloat				transi;
}						t_obj;

/*
** d - OpenGL structs (program <-> GPU)
*/

typedef struct			s_sha
{
	GLuint				vert;
	GLuint				frag;
	GLuint				prog;
}						t_sha;

typedef struct			s_buf
{
	GLuint				vao;
	GLuint				vbo;
	GLuint				nb_vertex;
	GLuint				ebo;
	GLuint				tex;
}						t_buf;

typedef struct			s_uni
{
	GLuint				transfo;
	GLuint				transi;
}						t_uni;

typedef struct			s_att
{
	GLuint				pos;
	GLuint				tex;
	GLuint				nor;
	GLuint				col;
}						t_att;

typedef struct			s_loc
{
	t_uni				u;
	t_att				a;
}						t_loc;

typedef struct			s_gl
{
	t_sha				sha;
	t_buf				buf;
	t_loc				loc;
}						t_gl;

/*
** e - global environnement
*/

typedef struct			s_env
{
	t_cam				c;
	t_obj				o;
	float				proj_m[4][4];
	float				transfo_m[4][4];
	char				key_tab[6];
	char				*obj_tab[10];
	char				**xpm_tab[6];
	GLFWwindow			*win;
	t_gl				gl;
}						t_env;

/*
** II - FUNCTION PROTOTYPES
*/

/*
** a - initialisation
*/

int						init_glfw(t_env *e);
void					set_callback(t_env *e);
int						init_glad(void);
void					load_shader(t_env *e);
void					load_program(t_env *e);
void					init_gl_buffers(t_env *e);
void					init_cam_obj_vertex_and_tex_structs(t_env *e);
void					cpy_m(float dst[4][4], float src[4][4]);
void					init_projection_matrix_and_uniform_att_ids(t_env *e);

/*
** b - file.obj parser
*/

int						f_triangle_number(char *str, t_f_obj_p *o);
int						recup_size(int fd, t_f_obj_p *o);
void					parsing_alloc(t_f_obj_p *o);
int						parsing_desalloc(t_f_obj_p *o);

int						verif_vtn_in_f(t_f_obj_p *o, int i);
int						verif_f(char *tab, t_f_obj_p *o);
int						nb_param_error(char **tab, int x);
int						vn_only_error(char *tab, t_f_obj_p *o);
int						invalid_face_error_msg(int nb);

void					init_f_obj_p(t_f_obj_p *o);
int						fill_f_obj_p(char *str, int *i, t_f_obj_p *o);
void					fill_vertex_struct(t_f_obj_p *o, t_env *e);

int						load_f_obj_data(char id, t_env *e);

/*
** c - file.xpm parser
*/

void					load_sqr_xpm(char **xpm, t_env *e);
void					tex_desalloc(t_env *e);

/*
** d - speak with GPU
*/

void					compute_and_send_uniform_atts_to_shaders(t_env *e);
void					gl_triangle_colors(t_env *e);
void					gl_texture(t_env *e);

void					send_data_to_gpu(t_env *e, int id);

/*
** e - other
*/

void					mouv_cam(t_env *c);
void					exit_all(t_env *e);

#endif
