/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:26:35 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 13:22:18 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_pipe(int p[2])
{
	if (pipe(p) < 0)
	{
		ft_putstr_fd("Error: can't create a pipe\n", 2);
		exit (1);
	}
	return (*p);
}

int	ft_open(const char *file, int flags, int permission)
{
	int	fd;

	fd = open(file, flags, permission);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Can't open file\n", 2);
		exit (1);
	}
	return (fd);
}

int	ft_fork(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
	{
		ft_putstr_fd("Error: Can't fork a child\n", 2);
		exit (1);
	}
	return (child);
}

int	ft_close(int fd)
{
	if (close(fd) < 0)
	{
		ft_putstr_fd("Error: Can't close the fd\n", 2);
		exit (1);
	}
	return (0);
}
