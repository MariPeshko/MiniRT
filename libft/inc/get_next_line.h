/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:06 by sgramsch          #+#    #+#             */
/*   Updated: 2024/04/07 11:56:34 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen(char *s);
char	*extract_return_line(char *safetycopy);
char	*edit_safetycopy(char *safetycopy);
int		end_of_line(char *safetycopy);
char	*append_safetycopy(char *safetycopy, char *reading);
char	*read_line(int fd, char *reading, char *safetycopy);
char	*gnl_free(char *a);

#endif
