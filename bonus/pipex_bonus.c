/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:34:29 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/30 22:45:49 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc(t_data *data, char *limiter)
{
	int		fd;
	char	*line;

	fd = ft_open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "heredoc>>", 9);
		line = get_next_line(0);
		if (line == NULL)
			exit (1);
		if ((ft_strlen(line) == ft_strlen(limiter) + 1) \
		&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			ft_close(fd);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	pipex(int argc, char **argv, t_data *data, char **envp)
{
	int		status;
	pid_t	*children;

	children = ft_calloc(data->ncmd + 1, sizeof(pid_t));
	children[data->ncmd] = '\0';
	ft_pipe(data->pipe1);
	children[0] = ft_fork();
	if (children[0] == 0)
		eldest_child(data->f1, argv[2 + data->hd], data, envp);
	ft_close(data->pipe1[1]);
	loop_mid(data, children, argv, envp);
	children[data->ncmd - 1] = ft_fork();
	if (children[data->ncmd - 1] == 0)
		youngest(data->f2, argv[argc - 2], data, envp);
	ft_close(data->pipe1[0]);
	waitpid(-1, &status, 0);
	free(children);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	error_checking(&data, argc, argv);
	init_data(argc, argv, envp, &data);
	if (data.hd == 1)
	{
		data.f1 = ft_open(".here_doc_tmp", O_RDONLY, 0644);
		data.f2 = ft_open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0666);
	}
	else
	{
		data.f1 = ft_open(argv[1], O_RDONLY, 0666);
		data.f2 = ft_open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	}
	pipex(argc, argv, &data, envp);
	free_semua(&data);
	return (0);
}
