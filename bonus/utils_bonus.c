/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:43:51 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 12:59:58 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->ncmd = argc - 3 - data->hd;
	split_path(data, argc, argv, envp);
}

int	wr_n_argc(int num, int argc)
{
	if (argc < num)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit (1);
	}
	return (0);
}

int	error_checking(t_data *data, int argc, char **argv)
{
	data->hd = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		data->hd = 1;
		wr_n_argc(6, argc);
		here_doc(data, argv[2]);
	}
	if (data->hd == 0)
	{	
		wr_n_argc(5, argc);
		if (access(argv[1], F_OK & (R_OK & X_OK)) != 0)
		{
			ft_putstr_fd("Error: No such file\n", 2);
			exit (1);
		}
	}
	return (0);
}

void	free_twod(char **twod)
{
	char	*temp;
	int		a;

	a = -1;
	while (twod[++a])
	{
		temp = twod[a];
		free(temp);
	}
	free(twod);
}

void	free_semua(t_data *data)
{
	free_twod(data->envp);
	free_twod(data->path);
	ft_close(data->f1);
	ft_close(data->f2);
}
