/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:40:17 by gpinchon          #+#    #+#             */
/*   Updated: 2016/05/18 17:15:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define BUFF_SIZE 1024

void			*ft_bzero(void *str, size_t n);
void			*ft_memccpy(void *str1, const void *str2, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
void			*ft_memcpy(void *str1, const void *str2, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t num);
void			*ft_memset(void *str, int c, size_t n);
void			ft_putstr(char *str);
void			ft_putchar(char c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *str);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, int n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strnstr(const char *str, const char *to_find, size_t size);
int				ft_strcmp(char *s1, char *s2);
int				ft_atoi(char *str);
int				ft_strncmp(const char *string1, const char *string2, int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_memdel(void **ap);
void			*ft_memalloc(size_t size);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
char			*ft_strmap(char const *s, char(*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_strrev(char *str);
char			*ft_itoa(int n);
void			ft_charswap(char *a, char *b);
void			ft_intswap(int *a, int *b);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				get_next_line(int const fd, char **line);
float			clamp(float nbr, float min, float max);
long int		clamp_int(long int nbr, long int min, long int max);
size_t			wordcount(const char *str, char c);
float			cycle_float(float nbr, float min, float max);
int				cycle_int(int nbr, int min, int max);
unsigned int	count_char(const char *str, char c);
size_t			wordcount(const char *str, char c);
char			*file_to_str(int fd);

#endif
