/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:42:21 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/22 18:45:30 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct sdata
{
	int		ncmd;
	char	**envp;
	char	**path;
	int		**pipe;
	int		pipeline[2];
}	t_data;

//path
void	split_path(t_data *data, int argc, char **argv, char **envp);
void	check_path(t_data *data, int argc, char **argv);
char	*exist_or_not(t_data *data, char *argv);
char	*split_argv(t_data *data, char *argv);

//utils
int		error_checking(int argc, char **argv);
void	free_twod(char **twod);
void	free_semua(t_data *data, int f1, int f2);

#endif