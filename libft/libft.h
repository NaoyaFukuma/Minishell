/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:09:46 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/17 12:37:26 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include "get_next_line_bonus.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_l
{
	void		*content;
	struct s_l	*next;
}				t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *str);
void			*ft_memset(void *buf, int c, size_t size);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t size);
void			*ft_memchr(const void *buf, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t size);
char			*ft_strnstr(const char *str, const char *target, size_t size);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t num, size_t size);
char			*ft_strdup(const char *str);
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *str, const char *set);
char			**ft_split(const char *str, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *str, int fd);
void			ft_putendl_fd(char const *str, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
char			*ft_ultoa(unsigned long n);
char			*ft_ultoa_base(unsigned long n, int base, char *base_set);
int				ft_pow(int num, size_t pow);
void			*ft_remalloc(void *old, size_t new_size, size_t old_size);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
void			ft_safe_free_single_ptr(void **target);
void			ft_safe_free_double_ptr(void ***target);
char			*ft_strcpy_forward(char *dest, char *src);
bool			ft_atoi_limit(const char *str, int *return_value);
void			ft_puthex_fd(unsigned int n, bool format, int fd);
void			ft_puthex_ul_fd(unsigned long n, bool format, int fd);

#endif
