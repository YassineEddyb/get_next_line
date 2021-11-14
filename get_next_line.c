/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:39:38 by yed-dyb           #+#    #+#             */
/*   Updated: 2021/11/14 17:49:08 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h>
#include<fcntl.h>

int has_new_line(char *buf)
{
    int i = 0;
    while(buf[i])
    {
        if (buf[i] == '\n' || buf[i] == '\0')
            return 1;
        i++;
    }
    return (0);
}

char *get_remain(char *str)
{
    char *remain;
    int i;
    int len;

    i = 0;
    while(str[len] && str[len] != '\n')
       i++;
    len = ft_strlen(str) - i;
    remain = malloc(len * sizeof(char));
    ft_strlcpy(remain, str + i, len);
    return (remain);
}

char *get_line(char *str, char *line) {
    int len;

    len = 0;
    while(str[len] && str[len] != '\n')
        len++;
    line = malloc((len + 2) * sizeof(char));
    ft_strlcpy(line, str, len + 2);
    return (line);
}

char *get_next_line(int fd)
{
    char *buff;
    char *str;
    char *line;
    int size;

    buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
    while(!has_new_line(str) )
    {
        size = read(fd, buff, BUFFER_SIZE);
        buff[size] = '\0';
        str = ft_strjoin(str, buff);
    }
    line = get_line(str, line);
    str = get_remain(str);
    return(line);
}

int main()
{
    int fd = open("test.txt", 2);
    int i = 0;
    //get_next_line(fd);
    while(i < 6) {
        printf("%s", get_next_line(fd));
      i++;
    }
}
