/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:34:29 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 20:18:10 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	eldest_child(int f1, char *argv, t_data *data, char **envp)
{
	char	**cmd;

	dup2(f1, 0);
	close(f1);
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
	ft_close(data->pipe1[1]);
	cmd = ft_split(argv, ' ');
	if (execve(data->path[1], cmd, envp) == -1)
	{
		ft_putstr_fd("Error:\n", 2);
		exit (1);
	}
}

void	pipex(char **argv, t_data *data, char **envp)
{
	int		status;
	pid_t	*children;

	children = ft_calloc(data->ncmd + 1, sizeof(pid_t));
	children[data->ncmd] = '\0';
	if (pipe(data->pipe1) < 0)
		ft_putstr_fd("Error: can't fork a child process\n", 2);
	children[0] = fork();
	if (children[0] < 0)
		return (perror("Fork: 1"));
	if (children[0] == 0)
		eldest_child(data->f1, argv[2], data, envp);
	children[1] = fork();
	if (children[1] < 0)
		return (perror("Fork: 2"));
	if (children[1] == 0)
		youngest(data->f2, argv[3], data, envp);
	ft_close(data->pipe1[1]);
	ft_close(data->pipe1[0]);
	waitpid(-1, &status, 0);
	free(children);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (error_checking(argc, argv) != 0)
		return (-1);
	init_data(argc, argv, envp, &data);
	data.f1 = open(argv[1], O_RDONLY, 0666);
	data.f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (data.f1 < 0 || data.f2 < 0)
		return (-1);
	pipex(argv, &data, envp);
	free_semua(&data);
	return (0);
}
