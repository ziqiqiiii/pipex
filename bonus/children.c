/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:17:52 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 20:59:58 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	eldest_child(int f1, char *argv, t_data *data, char **envp)
{
	char	**cmd;

	dup2(f1, 0);
	ft_close(f1);
	dup2(data->pipe1[1], 1);
	ft_close(data->pipe1[1]);
	ft_close(data->pipe1[0]);
	cmd = ft_split(argv, ' ');
	if (execve(data->path[0], cmd, envp) == -1)
	{
		ft_putstr_fd("Error:\n", 2);
		exit (1);
	}
}

void	youngest(int f2, char *argv, t_data *data, char **envp)
{
	char	**cmd;

	dup2(f2, 1);
	close(f2);
	dup2(data->pipe1[0], 0);
	ft_close(data->pipe1[0]);
	cmd = ft_split(argv, ' ');
	if (execve(data->path[data->ncmd - 1], cmd, envp) == -1)
	{
		ft_putstr_fd("Error:\n", 2);
		exit (1);
	}
}

void	middle_children(char *argv, t_data *data, char **envp, int i)
{
	char	**cmd;
	int		pipe2[2];

	dup2(data->fd, 0);
	ft_close(data->pipe1[0]);
	dup2(data->pipe1[1], 1);
	ft_close(data->pipe1[1]);
	cmd = ft_split(argv, ' ');
	if (execve(data->path[i], cmd, envp) == -1)
	{
		ft_putstr_fd("Error:\n", 2);
		exit (1);
	}
}

void	loop_mid(t_data *data, pid_t *children, char **argv, char **envp)
{
	int	i;
	int	status;

	i = 1;
	while (i < data->ncmd - 1)
	{
		data->fd = data->pipe1[0];
		ft_pipe(data->pipe1);
		children[i] = ft_fork();
		if (children[i] == 0)
			middle_children(argv[i + 2 + data->hd], data, envp, i);
		ft_close(data->pipe1[1]);
		ft_close(data->fd);
		waitpid(-1, &status, 0);
		i++;
	}
}
