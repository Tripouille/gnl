/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 12:13:38 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 12:52:06 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Main function. Fills line and returns 1 (or 0 on EOF or -1 on error).
*/

int					get_next_line(int fd, char **line)
{
	static t_fd_list	*begin = 0;
	t_fd_list			*fd_list;
	int					nl;

	if (!(fd_list = get_fd_list(fd, &begin)))
		return (clear_all(&begin));
	if (fd_list->b_list->start > 0)
	{
		nl = delta_to_nl(fd_list->b_list);
		if (nl != -1 || str_len(fd_list->b_list->b) < BUFFER_SIZE)
			return (fill_line(line, nl, fd_list, &begin));
		if (!add_b_list(fd_list))
			return (clear_all(&begin));
	}
	if (fill_buffers(fd, fd_list, &begin) == -1)
		return (-1);
	return (fill_line(line, delta_to_nl(fd_list->b_list), fd_list, &begin));
}

t_fd_list			*get_fd_list(int fd, t_fd_list **begin)
{
	t_fd_list	*tmp;

	tmp = *begin;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (!tmp)
	{
		if (!(tmp = new_fd_list(fd)))
			return (0);
		tmp->next = *begin;
		*begin = tmp;
	}
	return (tmp);
}

int					fill_buffers(int fd, t_fd_list *fd_list, t_fd_list **begin)
{
	int			ret;
	int			nl;
	t_b_list	*tmp;

	while ((ret = read(fd, fd_list->b_list->b, BUFFER_SIZE)) == BUFFER_SIZE
	&& ret && (nl = delta_to_nl(fd_list->b_list)) != -1)
	{
		fd_list->b_list->b[ret] = '\0';
		if (!add_b_list(fd_list))
			return (clear_all(begin));
	}
	if (ret < 0)
	{
		while (fd_list->b_list)
		{
			tmp = fd_list->b_list;
			fd_list->b_list = fd_list->b_list->next;
			free(tmp);
		}
		remove_fd(fd_list, begin);
		return (-1);
	}
	fd_list->b_list->b[ret] = '\0';
	return (1);
}

int					fill_line(char **line, int nl, t_fd_list *fd_list,
					t_fd_list **begin)
{
	int			len;
	int			size;
	t_b_list	*b_list;

	b_list = fd_list->b_list;
	size = nl != -1 ? nl : str_len(b_list->b + b_list->start);
	while ((b_list = b_list->next))
		size += str_len(b_list->b + b_list->start);
	if (!(*line = malloc(sizeof(**line) * (size + 1))))
		return (clear_all(begin));
	(*line)[size] = 0;
	b_list = fd_list->b_list;
	while (b_list)
	{
		len = str_len(b_list->b + b_list->start);
		while (len)
			(*line)[--size] = b_list->b[--len];
		b_list = b_list->next;
	}
	return (nl != -1 ? 0 : 1);
}

void				remove_fd(t_fd_list *fd_list, t_fd_list **begin)
{
	t_fd_list	*prev;
	t_fd_list	*tmp;

	if (fd_list == *begin)
	{
		*begin = (*begin)->next;
		free(fd_list);
		return ;
	}
	tmp = *begin;
	while (fd_list != tmp)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = fd_list->next;
	free(fd_list);
}
