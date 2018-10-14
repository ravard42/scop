/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 08:38:45 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 16:58:52 by ravard           ###   ########.fr       */
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
** I - PARSING STRUCTS
*/

typedef struct			s_objf
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

}						t_objf;

typedef struct			s_xpmf
{
	int					size;
	int					ncolors;
	int					chars_per_pixel;
	char				**ascii;
	int					*hexa;
	char				*data_line;
}						t_xpmf;

/*
** II - HEAP (tas) DYNAMICAL ALLOCATION DATA AND TEXTURE TO 3D RENDER
*/

typedef struct			s_data
{
	int					nb_vtnc;
	GLfloat				*vtnc;
	int					nb_elem;
	GLint				*elem;
}						t_data;

typedef struct			s_tex
{
	int					nb_pix;
	GLfloat				*pix;
}						t_tex;

/*
**  III - CAM AND OBJ
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
	t_data				d;
	t_tex				t;
	char				rot;
	char				angle_rot;
	float				rot_m[4][4];
	char				tex;
	GLfloat				transi;
}						t_obj;

/*
** IV - VARIABLES OPENGL (dialogue programme <-> carte graphique ...)
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
** V - GLOBAL ENVIRONNEMENT
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

int						init_glfw(t_env *e);
int						init_glad(void);
void					cpy_m(float dst[4][4], float src[4][4]);
void					init_projection_matrix_and_uniform_att_ids(t_env *e);
void					init_gl_buffers(t_env *e);
void					init_cam_obj_data_tex_structs(t_env *e);
void					gl_triangle_colors(t_env *e);
void					gl_texture(t_env *e);
void					set_callback(t_env *e);

void					load_shader(t_env *e);
void					load_program(t_env *e);

void					load_sqr_xpm(char **xpm, t_env *e);

// PARSER


int						f_triangle_number(char *str, t_objf *o);
int						recup_size(int fd, t_objf *o);
void					parsing_alloc(t_objf *o);
int						parsing_desalloc(t_objf *o);

int						verif_vtn_nb_coord(char **tab, int nb);
int						verif_vtn_in_f(t_objf *o, int i);
int						verif_f(char *tab, t_objf *o);

int						nb_param_error(char **tab, int x);
int						vn_only_error(char *tab, t_objf *o);
int						invalid_face_error_msg(int nb);

void					init_objf(t_objf *o);
int						fill_objf(char *str, int *i, t_objf *o);
void					fill_data_struct(t_objf *o, t_env *e);

int						load_obj_data(char id, t_env *e);

// SEND DATA TO GPU 

void					send_data_to_gpu(t_env *e, int id);
void					data_desalloc(t_env *e);



void					tex_desalloc(t_env *e);
void					mouv_cam(t_env *c);
void					compute_and_send_uniform_atts_to_shaders(t_env *e);
void					handle_texture_and_color(t_env *e);
void					exit_all(t_env *e);

#endif
