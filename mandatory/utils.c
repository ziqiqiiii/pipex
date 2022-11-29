/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:43:51 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 20:14:17 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(int argc, char **argv, char **envp, t_data *data)
{
	data->ncmd = argc - 3;
	split_path(data, argc, argv, envp);
}

int	error_checking(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (-1);
	}
	if (access(argv[1], F_OK & (R_OK & X_OK)) != 0)
	{
		ft_putstr_fd("Error: No such file\n", 2);
		return (-1);
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
