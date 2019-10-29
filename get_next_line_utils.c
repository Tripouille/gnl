/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 12:14:08 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 12:49:56 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Creates a new t_list element associated to the given fd.
*/

t_fd_list			*new_fd_list(int fd)
{
	t_fd_list		*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->b_list = NULL;
	if (!(add_b_list(new)))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int					add_b_list(t_fd_list *fd_list)
{
	t_b_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->b[0] = '\0';
	new->start = 0;
	new->next = fd_list->b_list;
	fd_list->b_list = new;
	return (1);
}

int					clear_all(t_fd_list **begin)
{
	t_b_list	*tmp;

	if (!begin || !*begin)
		return (-1);
	clear_all(&(*begin)->next);
	while ((*begin)->b_list)
	{
		tmp = (*begin)->b_list;
		(*begin)->b_list = (*begin)->b_list->next;
		free(tmp);
	}
	free(*begin);
	*begin = NULL;
	return (-1);
}

int					delta_to_nl(t_b_list *b_list)
{
	int		i;

	i = 0;
	while (b_list->b[b_list->start + i]
	&& b_list->b[b_list->start + i] != '\n')
		i++;
	return (b_list->b[i] == '\n' ? i : -1);
}

int					str_len(const char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
