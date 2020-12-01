/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:13:47 by jgambard          #+#    #+#             */
/*   Updated: 2020/12/01 07:40:22 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct			s_b_list
{
	char				b[BUFFER_SIZE + 1];
	int					start;
	struct s_b_list		*next;
}						t_b_list;

typedef struct			s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
	t_b_list			*b_list;
}						t_fd_list;

int						get_next_line(int fd, char **line);
int						set_fd_list(int fd, t_fd_list **begin);
int						fill_buffers(int fd, t_fd_list **begin);
int						fill_line(char **line, int nl, t_fd_list **begin);
int						malloc_line(char **line, int nl, t_fd_list **begin);

t_fd_list				*new_fd_list(int fd);
int						add_b_list(t_fd_list *fd_list);
int						remove_fd(t_fd_list **begin, int all);
int						delta_to_nl(t_b_list *b_list);
int						str_len(const char *str);

#endif
