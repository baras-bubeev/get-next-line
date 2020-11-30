/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpowder <mpowder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 05:49:19 by mpowder           #+#    #+#             */
/*   Updated: 2020/11/30 13:40:35 by mpowder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_buf(char **line, char *buf)
{
	char	*p;
	char	*tmp;

	p = 0;
	if (buf)
	{
		tmp = *line;
		if ((p = ft_strchr(buf, '\n')))
		{
			*p = 0;
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			free(tmp);
			ft_strcpy(buf, ++p);
			return (1);
		}
		else
		{
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			*buf = 0;
			free(tmp);
		}
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buf[1024][BUFFER_SIZE + 1];
	int			byte;
	int			fl;

	if ((read(fd, buf[fd], 0)) < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((fl = ft_check_buf(line, buf[fd])))
		return (fl);
	while ((byte = read(fd, buf[fd], BUFFER_SIZE)))
	{
		buf[fd][byte] = 0;
		if ((fl = ft_check_buf(line, buf[fd])))
			return (fl);
		if (byte < BUFFER_SIZE)
			return (0);
	}
	return (0);
}
