/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:37:31 by ssukhova          #+#    #+#             */
/*   Updated: 2023/12/22 15:02:11 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*temp_allocation(char *temp, char *buffer)
{
	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free (buffer);
		return (NULL);
	}
	return (temp);
}

static char	*concatenate_and_free_old(char *buffer, char *temp)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

static char	*free_and_return(void *first, void *second)
{
	free(first);
	free(second);
	return (NULL);
}

static char	*read_from_file(int fd, char *buffer)
{
	int		bytes_read;
	char	*temp;

	temp = NULL;
	temp = temp_allocation(temp, buffer);
	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if ((bytes_read < 0) || ((ft_strlen(buffer) == 0) && (bytes_read == 0)))
			return (free_and_return(buffer, temp));
		if (bytes_read == 0 && ft_strlen(buffer) != 0)
		{
			free(temp);
			return (buffer);
		}
		temp[bytes_read] = '\0';
		buffer = concatenate_and_free_old(buffer, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*new_line_ptr;
	char		*temp;

	if (!buffer)
		buffer = ft_strdup("");
	buffer = read_from_file(fd, buffer);
	if (!buffer || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line_ptr = ft_strchr(buffer, '\n');
	if (!new_line_ptr)
	{
		line = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
	}
	if (new_line_ptr)
	{
		line = ft_substr(buffer, 0, new_line_ptr - buffer + 1);
		temp = ft_strdup(new_line_ptr + 1);
		free(buffer);
		buffer = temp;
	}
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*next_line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	next_line = get_next_line(fd);
	while (next_line != NULL)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
