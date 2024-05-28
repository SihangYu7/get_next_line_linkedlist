/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyu <siyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:19 by siyu              #+#    #+#             */
/*   Updated: 2024/05/28 16:11:06 by siyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*read_file(int fd, t_list *lst)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	t_list	*next;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buffer)));
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		while (lst != NULL)
		{
			next = lst->next;
			free(lst->content);
			free(lst);
			lst = next;
		}
		return (NULL);
	}
	return (lst);
}

char	*extract_line(t_list *lst, size_t len)
{
	t_list	*temp;
	char	*line;
	size_t	i;
	char	*content;

	i = 0;
	temp = lst;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	content = temp->content;
	while (temp && i < len)
	{
		while (*content && i < len)
			line[i++] = *content++;
		temp = temp->next;
	}
	line[len] = '\0';
	return (line);
}

void	update_list(t_list **lst, char *line)
{
	t_list	*temp;
	size_t	line_len;
	size_t	node_len;
	char	*remainder;

	line_len = ft_strlen(line);
	while (*lst && line_len > 0)
	{
		node_len = ft_strlen((*lst)->content);
		if (node_len <= line_len)
		{
			line_len -= node_len;
			temp = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			*lst = temp;
		}
		else
		{
			remainder = ft_strdup(&(*lst)->content[line_len]);
			free((*lst)->content);
			(*lst)->content = remainder;
			break ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	size_t			len;
	t_list			*temp;
	char			*newline_char_pos;

	len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst = read_file(fd, lst);
	if (!lst)
		return (NULL);
	temp = lst;
	newline_char_pos = ft_strchr(temp->content, '\n');
	while (temp && !(newline_char_pos))
	{
		len += ft_strlen(temp->content);
		temp = temp->next;
	}
	if (newline_char_pos)
		len += ft_strlen(temp->content);
	line = extract_line(lst, len);
	update_list(&lst, line);
	return (line);
}
