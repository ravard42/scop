/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 03:30:05 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 10:41:44 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>

# define MAX_FD 2048
# define BUFF_SIZE 7
# define MARGE 5

typedef struct		s_flags
{
	char			hash;
	char			min;
	char			plu;
	char			sp;
	char			ze;
}					t_flags;

typedef struct		s_buff
{
	char			*b;
	int				ret;
}					t_buff;

typedef struct		s_spe
{
	t_flags			fl;
	int				w;
	int				pre;
	char			size;
	char			type;
	t_buff			buff;
	char			*out;
	int				c_null_conv;
}					t_spe;

typedef struct		s_conv
{
	char			*s;
	void			(*f)(va_list *va, t_spe *e);
}					t_conv;

char				*ft_strdup(const char *str);
char				**ft_strsplit(const char *s, char c);
char				**malloc_empty_str_tab(void);
int					free_ok(void *ptr);
int					free_split(char **tab);
void				*ft_memalloc(size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					get_next_line(int fd, char **line);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_printf(const char *format, ...);
int					conv(char *str, const char *s, va_list *va,
						t_conv const *tab);
void				c_conv(va_list *va, t_spe *sp);
void				s_conv(va_list *va, t_spe *sp);
void				d_conv(va_list *va, t_spe *sp);
void				oux_conv(va_list *va, t_spe *sp);
void				bin_conv(va_list *va, t_spe *sp);
void				undefined_conv(va_list *va, t_spe *sp);
int					extract_specifier(char const *s, t_spe *spe);
void				putchar_buffer(char c, char *buff);
void				putstr_buffer(char *str, char *buff);
void				putnbr_buffer(intmax_t n, char *buff);
void				putbnbr_buffer(uintmax_t n, char *param, char *buff);
int					ft_atoi(const char *str);
int					ft_hexatoi(const char *str);
char				*rm_begin_whitespace(char *str);
char				*rm_multi_whitespace(char *str);
char				*polarity(char *str, int *sign);
int					ft_len(char *buf, char mode);
int					ft_power(int x, int n);
void				ft_exit(char *error);
void				ft_memset(char *b, char c, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					catch_pos_numb(char *s);
void				init_spe(t_spe *sp);
char				*ft_revstr(char *str);
size_t				ft_strlen(const char *s);
int					wstrlen(wchar_t *wc);
char				*add_nose(int n, char c, char *buff);
char				*add_tail(int n, char c, char *buff);
void				my_putstr(char *str);
int					write_no_spe(char const *s, t_spe *sp);
void				write_spe(t_spe *sp);
char				*buff_malloc(int *offset, char const *s, t_spe *sp);
void				d_malloc(intmax_t i, t_spe *sp);
void				oux_malloc(uintmax_t i, char b, t_spe *sp);
void				c_malloc(char nb_char, t_spe *sp);
void				s_malloc(char *str, t_spe *sp);
int					utf_32_to_8(wchar_t utf_32, char *utf_8);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				ft_toupper(char c);

#endif
