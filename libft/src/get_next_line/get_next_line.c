/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:30:39 by sgramsch          #+#    #+#             */
/*   Updated: 2024/01/16 16:30:39 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/libft_gnl_printf.h"
#include "../../inc/libft.h"
#include "../../inc/get_next_line.h"

char	*extract_return_line(char *safetycopy)
{
	size_t	pos;
	char	*return_line;

	pos = 0;
	if (!safetycopy[pos])
		return (NULL);
	while (safetycopy[pos] && safetycopy[pos] != '\n')
		pos ++;
	return_line = (char *)malloc((pos + 2) * sizeof(char));
	if (!return_line)
		return (NULL);
	pos = 0;
	while (safetycopy[pos] && safetycopy[pos] != '\n')
	{
		return_line[pos] = safetycopy[pos];
		pos ++;
	}
	if (safetycopy[pos] == '\n')
	{
		return_line[pos] = safetycopy[pos];
		pos ++;
	}
	return_line[pos] = '\0';
	return (return_line);
}

char	*edit_safetycopy(char *safetycopy)
{
	char	*edited;
	size_t	pos;
	size_t	pos2;

	pos = 0;
	if (!safetycopy)
		return (NULL);
	while (safetycopy[pos] && safetycopy[pos] != '\n')
		pos ++;
	if (!safetycopy[pos])
		return (gnl_free(safetycopy));
	if (!safetycopy[pos + 1])
		return (gnl_free(safetycopy));
	edited = (char *)malloc((gnl_strlen(safetycopy) - pos + 1) * sizeof(char));
	if (!edited)
		return (NULL);
	pos ++;
	pos2 = -1;
	while (safetycopy[pos + ++pos2] != '\0')
		edited[pos2] = safetycopy[pos + pos2];
	edited[pos2] = '\0';
	if (safetycopy)
		safetycopy = gnl_free(safetycopy);
	return (edited);
}

char	*append_safetycopy(char *sc, char *read)
{
	int		pos;
	int		pos2;
	char	*appended;

	pos = 0;
	pos2 = -1;
	if (!sc)
	{
		sc = (char *)malloc(1 * sizeof(char));
		if (!sc || !read)
			return (NULL);
		sc[0] = '\0';
	}
	appended = malloc((gnl_strlen(sc) + gnl_strlen(read) + 1) * sizeof(char));
	if (!appended)
		return (NULL);
	pos --;
	while (sc[++pos])
		appended[pos] = sc[pos];
	while (read[++pos2])
		appended[pos + pos2] = read[pos2];
	appended[pos + pos2] = '\0';
	sc = gnl_free(sc);
	return (appended);
}

char	*read_line(int fd, char *reading, char *safetycopy)
{
	int	progress;

	progress = 1;
	while ((end_of_line(safetycopy) == -1) && progress > 0)
	{
		progress = read(fd, reading, BUFFER_SIZE);
		if (progress == -1)
			return (gnl_free(safetycopy));
		if (progress == 0)
			break ;
		reading[progress] = '\0';
		safetycopy = append_safetycopy(safetycopy, reading);
	}
	return (safetycopy);
}

char	*get_next_line(int fd)
{
	char			*reading;
	static char		*safetycopy;
	char			*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reading = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!reading)
		return (NULL);
	safetycopy = read_line(fd, reading, safetycopy);
	reading = gnl_free(reading);
	if (safetycopy == NULL)
		return (NULL);
	return_line = extract_return_line(safetycopy);
	safetycopy = edit_safetycopy(safetycopy);
	return (return_line);
}
/*
int main(void)
{
	int fd = open("test", O_RDONLY);
	printf("\nfd = %d\n", fd);
	char	*a;
	a = get_next_line(fd);
	while (a != NULL)
	{
		printf("result:%s", a);
		free(a); //this missing causes the leaks
		a = get_next_line(fd);
	}
	
	free(a);
	close(fd);
	// printf("result:%s", get_next_line(fd));
	// printf("result:%s", get_next_line(fd));
	// printf("result:%s", get_next_line(fd));
	// printf("result:%s", get_next_line(fd));
	// printf("result:%s", get_next_line(fd));
//	printf("finished");
	return (0);
}*/
