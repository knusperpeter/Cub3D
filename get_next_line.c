/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:42:52 by jseidere          #+#    #+#             */
/*   Updated: 2024/06/28 12:48:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*double_str_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (0);
}

char	*return_function(int index, char **stash)
{
	char		*result;
	size_t		len;

	if (!*stash)
		return (NULL);
	if (index <= 0)
	{
		if (**stash == 0 || index < 0)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		result = *stash;
		*stash = NULL;
		return (result);
	}
	len = ft_strlen(*stash) - index;
	result = *stash;
	*stash = ft_substr(*stash, index, len);
	if (!*stash)
		return (double_str_free(result, *stash));
	result[index] = '\0';
	return (result);
}

char	*get_line(char **stash, char *buffer, int fd)
{
	char	*new_stash;
	char	*result;
	char	*next_line;
	ssize_t	bytesread;

	next_line = ft_strchr(*stash, '\n');
	while (next_line == NULL)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread <= 0)
			return (return_function(bytesread, stash));
		buffer[bytesread] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		if (!new_stash)
		{
			free(*stash);
			return (NULL);
		}
		free(*stash);
		*stash = new_stash;
		next_line = ft_strchr(*stash, '\n');
	}
	result = return_function(next_line - *stash + 1, stash);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	result = get_line(&stash, buffer, fd);
	free(buffer);
	return (result);
}
/* #include <stdio.h>
int main()
{
	int i = 1;

	int fd = open("text.txt", O_RDONLY);
	
	if (fd < 0)
	{
		perror("Fehler beim Öffnen der Datei");
		return 1;
	}

	char *line;
	
	while (i <= 12)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%d = %s\n", i, line);
			free(line);
		}
		else
		{
			printf("%d = Zeile nicht verfügbar\n", i);
		}
		printf("________________________\n");
	i++;
	}
	close(fd);
	return 0;
} */
/* 
#include <stdio.h>
int main ()
{
	int fd;
	int i;

	i = 0;
	//char *test = get_buffer(fd);
	
	fd = open ("text.txt", O_RDONLY);
	
	while(i < 27)
	{
		printf("%s\n", get_next_line(fd));
		i++;
	}
	//test = get_next_line(fd);
	
	//printf("%s\n", get_next_line(fd));

	close (fd);

	//return (0);
} */
