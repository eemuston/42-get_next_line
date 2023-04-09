/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:12:50 by eemuston          #+#    #+#             */
/*   Updated: 2022/11/30 18:09:15 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, t_wildstruct *tb, char *buf)
{
	int	re;

	re = 1;
	if (tb[fd].temp == 0)
	{
		tb[fd].temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tb[fd].temp)
			return (0);
		tb[fd].temp[0] = '\0';
	}
	while (!ft_strchr(buf, '\n') && re > 0)
	{
		re = read(fd, buf, BUFFER_SIZE);
		if (re <= 0)
			break ;
		else
		{
			buf[re] = '\0';
			tb[fd].temp = ft_strjoin_with_steroids(tb[fd].temp, buf);
		}
	}
	free(buf);
	return (tb[fd].temp);
}

int	temp_free(char *temp, int k)
{
	if (k == 0)
	{
		free(temp);
		temp = NULL;
		return (1);
	}
	return (0);
}

char	*bufsplitter(int fd, char *line, t_wildstruct *tb)
{	
	int			j;

	j = 0;
	if (tb[fd].k == 1)
		tb[fd].temp = NULL;
	if (!tb[fd].temp)
		return (0);
	if (tb[fd].temp[tb[fd].i] == '\0')
	{
		tb[fd].k = temp_free(tb[fd].temp, tb[fd].k);
		return (0);
	}
	line = malloc(sizeof(char) * (ft_strlen_h(&tb[fd].temp[tb[fd].i]) + 1));
	if (!line)
		return (0);
	while (tb[fd].temp[tb[fd].i] != '\n' && tb[fd].temp[tb[fd].i] != '\0')
		line[j++] = tb[fd].temp[tb[fd].i++];
	if (tb[fd].temp[tb[fd].i] == '\n')
		line[j++] = tb[fd].temp[tb[fd].i++];
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int					re;
	char				*buf;
	static t_wildstruct	tb[1000];
	char				*line;

	re = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 100));
	if (!buf)
		return (0);
	tb[fd].temp = read_line(fd, tb, buf);
	line = bufsplitter(fd, line, tb);
	return (line);
}
