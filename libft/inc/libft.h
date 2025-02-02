/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:06 by sgramsch          #+#    #+#             */
/*   Updated: 2024/04/07 11:56:34 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 42
// # endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(const char *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);

//printf
int		ft_printf(const char *format, ...);
int		ft_putnbr(int n, int size);
int		ft_putstr(char *s);
int		ft_putchar(unsigned char c);
int		ft_hexa(long long int n, int size, int up);
int		ft_putunsigned(unsigned int n, int size);

//get_next_line
// char	*extract_return_line(char *safetycopy);
// char	*edit_safetycopy(char *safetycopy);
// char	*append_safetycopy(char *sc, char *read);
// char	*read_line(int fd, char *reading, char *safetycopy);
// char	*get_next_line(int fd);
// int		end_of_line(char *safetycopy);
// size_t	gnl_strlen(char *s);
// char	*gnl_free(char *a);
// char	*get_next_line(int fd);
// size_t	gnl_strlen(char *s);
// char	*extract_return_line(char *safetycopy);
// char	*edit_safetycopy(char *safetycopy);
// int		end_of_line(char *safetycopy);
// char	*append_safetycopy(char *safetycopy, char *reading);
// char	*read_line(int fd, char *reading, char *safetycopy);
// char	*gnl_free(char *a);
#endif
