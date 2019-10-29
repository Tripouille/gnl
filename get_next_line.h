/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 12:13:47 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 12:51:56 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

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
t_fd_list				*get_fd_list(int fd, t_fd_list **begin);
int						fill_buffers(int fd, t_fd_list *fd_list,
						t_fd_list **begin);
int						fill_line(char **line, int nl, t_fd_list *fd_list,
						t_fd_list **begin);
void					remove_fd(t_fd_list *fd_list, t_fd_list **begin);

t_fd_list				*new_fd_list(int fd);
int						add_b_list(t_fd_list *fd_list);
int						clear_all(t_fd_list **begin);
int						delta_to_nl(t_b_list *b_list);
int						str_len(const char *str);

#endif
