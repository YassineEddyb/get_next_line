/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:59:19 by yed-dyb           #+#    #+#             */
/*   Updated: 2021/11/16 20:56:30 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<fcntl.h>
#include<stdio.h>

int has_new_line(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char *get_line(char *str)
{
    int len;
    char *line;

    len = 1;
    if(!str)
        return(NULL);
    while(str[len] && str[len] != '\n')
        len++;
    line = malloc((len + 2) * sizeof(char));
    ft_strlcpy(line, str, len + 2);
    return (line);
}

char *get_remain(char *str)
{
    int i;
    int len;
    char *remain;
    
    i = 0;
    if (!str)
        return (NULL);
    while(str[i])
        i++;
    len = ft_strlen(str) - i;
    remain = malloc((len + 1) * sizeof(char));
    ft_strlcpy(remain, str + i + 1, len + 1);
    free(str);
    return (remain);
}

char *get_next_line(int fd) {
    char buff[BUFFER_SIZE + 1];
    static char *save;
    char *line;
    int size;

    size = 1;
    while(!has_new_line(save) && size != 0)
    {
        size = read(fd, buff, BUFFER_SIZE);
        if (size == -1)
            return (NULL);
        buff[size] = 0;
        save = ft_strjoin(save, buff);
    }
    if (size == 0)
        return (0);
    line = get_line(save);
    save = get_remain(save);
    return (line);
}

int main()
{
    int fd = open("./test", 2);
    int i = 0;
    while(i < 3)
    {
        printf("%s", get_next_line(fd));
        i++;
    }
}
