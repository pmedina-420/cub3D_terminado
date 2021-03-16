/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:14:08 by pmedina-          #+#    #+#             */
/*   Updated: 2020/09/03 13:33:06 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		isneg(char **s, char **line)
{
	if (gn_strchr(*s, '\0'))
	{
		*line = gn_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (0);
}

int		bytesneg(ssize_t *nby, char **s)
{
	if (*nby < 0)
	{
		if (*s != NULL)
		{
			free(*s);
			*s = NULL;
		}
		return (-1);
	}
	return (0);
}

int		aux(ssize_t nby, char **s, char **line)
{
	char	*vt;
	char	*vt2;

	if (!nby && !*s)
	{
		*line = gn_strdup("");
		return (0);
	}
	if (bytesneg(&nby, &*s))
		return (-1);
	if ((vt = gn_strchr(*s, '\n')))
	{
		*vt = '\0';
		*line = gn_strdup(*s);
		vt2 = gn_strdup(vt + 1);
		free(*s);
		*s = vt2;
		return (1);
	}
	else if (isneg(&*s, &*line))
		return (0);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		*mem;
	static char	*x[4096];
	ssize_t		nby;
	char		*vt;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 ||
			(!(mem = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while ((nby = read(fd, mem, BUFFER_SIZE)) > 0)
	{
		mem[nby] = '\0';
		if (!x[fd])
			x[fd] = gn_strdup(mem);
		else
		{
			vt = gn_strjoin(x[fd], mem);
			free(x[fd]);
			x[fd] = vt;
		}
		if (gn_strchr(mem, '\n'))
			break ;
	}
	free(mem);
	mem = NULL;
	return (aux(nby, &x[fd], &*line));
}
