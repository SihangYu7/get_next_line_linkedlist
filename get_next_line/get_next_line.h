/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyu <siyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:41:03 by siyu              #+#    #+#             */
/*   Updated: 2024/06/04 13:40:28 by siyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int 	found_newline(t_list *linkedbuf);
t_list	*ft_lst_get_last(t_list *linkedbuf);
void	read_and_linkedbuf(int fd, t_list **linkedbuf);
void	add_to_linkedbuf(t_list **linkedbuf, char *buf, int readed);
void	extract_line(t_list *linkedbuf, char **line);
void	generate_line(char **line, t_list *linkedbuf);
void	clean_linkedbuf(t_list **linkedbuf);
int 	ft_strlen(const char *str);
void	free_linkedbuf(t_list *linkedbuf);
#endif
