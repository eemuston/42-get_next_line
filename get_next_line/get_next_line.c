/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eemuston <eemuston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:12:50 by eemuston          #+#    #+#             */
/*   Updated: 2022/11/30 14:10:10 by eemuston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *temp, char *buf, int fd)
{
	int	re;

	re = 1;
	if (temp == 0)
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (0);
		temp[0] = '\0';
	}
	while (!ft_strchr(buf, '\n') && re > 0)
	{
		re = read(fd, buf, BUFFER_SIZE);
		if (re <= 0)
			break ;
		else
		{
			buf[re] = '\0';
			temp = ft_strjoin_with_steroids(temp, buf);
		}
	}
	return (temp);
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

char	*bufsplitter(char *line, char *temp)
{	
	static int	i;
	int			j;
	static int	k;

	j = 0;
	if (k == 1)
		temp = NULL;
	if (!temp)
		return (0);
	if (temp[i] == '\0')
	{
		k = temp_free(temp, k);
		return (0);
	}
	line = malloc(sizeof(char) * (ft_strlen_with_steroids(&temp[i]) + 1));
	if (!line)
		return (0);
	while (temp[i] != '\n' && temp[i] != '\0')
		line[j++] = temp[i++];
	if (temp[i] == '\n')
		line[j++] = temp[i++];
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			re;
	char		buf[BUFFER_SIZE + 1];
	static char	*temp;
	char		*line;

	re = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	temp = read_line(temp, buf, fd);
	line = bufsplitter(line, temp);
	return (line);
}
