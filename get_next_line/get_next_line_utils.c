/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyu <siyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:58 by siyu              #+#    #+#             */
/*   Updated: 2024/06/04 13:40:33 by siyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *linkedbuf)
{
	int		i;
	t_list	*current;

	if (linkedbuf == NULL)
		return (0);
	current = ft_lst_get_last(linkedbuf);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_get_last(t_list *linkedbuf)
{
	t_list	*current;

	current = linkedbuf;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_list *linkedbuf)
{
	int	i;
	int	len;

	len = 0;
	while (linkedbuf)
	{
		i = 0;
		while (linkedbuf->content[i])
		{
			if (linkedbuf->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		linkedbuf = linkedbuf->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_linkedbuf(t_list *linkedbuf)
{
	t_list	*current;
	t_list	*next;

	current = linkedbuf;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
