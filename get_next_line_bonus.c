/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:24:09 by yed-dyb           #+#    #+#             */
/*   Updated: 2021/11/18 16:07:41 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, str, i + 1);
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_remain(char *str)
{
	int		i;
	char	*remain;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	remain = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!remain)
		return (NULL);
	i++;
	ft_strlcpy(remain, str + i, ft_strlen(str) - i + 1);
	free(str);
	return (remain);
}

char	*read_and_save(int fd, char *save)
{
	char	*buff;
	int		size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	size = 1;
	while (!has_new_line(save) && size != 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[size] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*arr[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	arr[fd] = read_and_save(fd, arr[fd]);
	if (!arr[fd])
		return (NULL);
	line = get_line(arr[fd]);
	arr[fd] = get_remain(arr[fd]);
	return (line);
}

// int main()
// {
//     int fd1 = open("./test", 2);
//     int fd2 = open("./test.txt", 2);
//     int i = 0;
//     // while(i < 3)
//     // {
//     printf("%s\n", get_next_line(fd1));
//     printf("%s\n", get_next_line(fd2));
//     printf("%s\n", get_next_line(fd1));
//     printf("%s\n", get_next_line(fd2));
//         // i++;
//     // }
// }
