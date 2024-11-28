/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esever <esever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:46:28 by esever            #+#    #+#             */
/*   Updated: 2024/11/28 13:55:11 by esever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *stash)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (!newline_exist(stash) && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if ((!stash && readed == 0) || readed == -1)
			return (free(buff), NULL);
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	return (stash);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		line[i] = stash[i];
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_rest(char *stash, char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = ft_strlen(line);
	if (!stash[i])
		return (free(stash), NULL);
	j = 0;
	while (stash[i++])
		j++;
	rest = malloc(sizeof(char) * (j + 1));
	if (!rest)
		return (NULL);
	i = ft_strlen(line);
	j = 0;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	return (free(stash), rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_file(fd, stash);
	if (!temp)
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = temp;
	line = ft_get_line(stash);
	stash = ft_get_rest(stash, line);
	return (line);
}
/*#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("a.txt", O_RDONLY);

    char *s;
    s = get_next_line(fd);
	printf("%s", s);
    close(fd); 

    return 0;
}*/
/*SATIRLARI TERSTEN YAZDIRMA
void print_reverse_lines(int fd)
{
	char *s = get_next_line(fd);

	if (s == NULL)
	{
		return;
	}

	print_reverse_lines(fd);
	
	printf("%s", s);
	free(s);
}
int main()
{
    int fd = open("a.txt", O_RDONLY);

    print_reverse_lines(fd);

    close(fd); 

    return 0;
}
*/

