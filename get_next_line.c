#include "get_next_line.h"
#include <stdio.h>

int	fill_the_line(char *s, char **line, int data)
{
	int		len;

	len = 0;
	if (s)
	{
		while (s[len] != '\n' && s[len] != '\0')
			len++;
	}
	if (s && s[len] == '\n')
	{
		if (*line != NULL)
			*line = NULL;
		*line = ft_substr(s, 0 ,len);
	}
	if (!s && data == 0)
	{
		if (*line != NULL)
			*line = NULL;
		*line = ft_strdup("");
		return (0);
	}
	else if (data == 0 && s[len] == '\0')
	{
		if (*line != NULL)
			*line = NULL;
		*line = ft_strdup(s);
		return (0);
	}
	return (1);
}

char	*keep_the_static(char *s)
{
	int	len;
	int	end;
	char	*tmp;

	len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	end = 0;
	while (s[end])
		end++;
	if (s[len] == '\n')
	{
		if ((end - len - 1) == 0)
		{
			if (s)
			{
				free(s);
				s = NULL;
			}
		}
		else
		{
			tmp = ft_substr(s, len + 1, end - len - 1);
			free(s);
			s = NULL;
			s = ft_strdup(tmp);
		}
	}
	return (s);
}

int	get_next_line(const int fd, char **line)
{
	static char	*s = NULL;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		data;

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	while ((data = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[data] = '\0';
		if (!s)
			s = ft_strdup(buf);
		else
		{
			tmp = NULL;
			tmp = ft_strjoin(s, buf);
			free(s);
			s = tmp;
		}
		if (ft_strchr(s, '\n'))
			break ;
	}
	if (data < 0)
		return (-1);
	if (fill_the_line(s, line, data) == 0)
	{
		s = NULL;
		return (0);
	}
	if (fill_the_line(s, line, data) == 1)
		s = keep_the_static(s);
	return (1);
}
