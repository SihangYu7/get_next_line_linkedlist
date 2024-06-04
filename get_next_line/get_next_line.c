/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyu <siyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:19 by siyu              #+#    #+#             */
/*   Updated: 2024/06/04 13:40:17 by siyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*linkedbuf = NULL;
	char			*line = NULL;


	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
        free_linkedbuf(linkedbuf);
        linkedbuf = NULL;
        return (NULL);
    }
	read_and_linkedbuf(fd, &linkedbuf);
	if (linkedbuf == NULL)
		return (NULL);
	extract_line(linkedbuf, &line);
	clean_linkedbuf(&linkedbuf);
	if (line[0] == '\0' && linkedbuf != NULL)
	{
        free(line);
		free_linkedbuf(linkedbuf);
		linkedbuf = NULL;
		return (NULL);
	}
	return (line);
}

void	read_and_linkedbuf(int fd, t_list **linkedbuf)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*linkedbuf) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buf);
            free_linkedbuf(*linkedbuf);
            *linkedbuf = NULL;
			return ;
		}
        if (*linkedbuf == NULL && readed == 0)
        {
            free(buf);
            return ;
        }
		buf[readed] = '\0';
		add_to_linkedbuf(linkedbuf, buf, readed);
		free(buf);
	}
}

void	add_to_linkedbuf(t_list **linkedbuf, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*linkedbuf == NULL)
	{
		*linkedbuf = new_node;
		return ;
	}
	last = ft_lst_get_last(*linkedbuf);
	last->next = new_node;
}

void	extract_line(t_list *linkedbuf, char **line)
{
	int	i;
	int	j;

	if (linkedbuf == NULL)
		return ;
	generate_line(line, linkedbuf);
	if (*line == NULL)
		return ;
	j = 0;
	while (linkedbuf)
	{
		i = 0;
		while (linkedbuf->content[i])
		{
			if (linkedbuf->content[i] == '\n')
			{
				(*line)[j++] = linkedbuf->content[i];
				break ;
			}
			(*line)[j++] = linkedbuf->content[i++];
		}
		linkedbuf = linkedbuf->next;
	}
	(*line)[j] = '\0';
}

void	clean_linkedbuf(t_list **linkedbuf)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (linkedbuf == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*linkedbuf);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_linkedbuf(*linkedbuf);
	*linkedbuf = clean_node;
}
