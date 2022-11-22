/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:42:21 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/22 21:45:15 by tzi-qi           ###   ########.fr       */
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


// f1 is fd for infile
// f2 is fd for outfile

// envp is split envp 
// path is the path for cmds

// pipeline is pipe

// int **pipes is used to store the pipes
// pipe[0] = pipe between eldest child process and first middle child process
// pipe[1] = pipe between first middle child 
// proces and second middle child process
// the list go on

typedef struct sdata
{
	int		f1;
	int		f2;
	int		ncmd;
	char	**envp;
	char	**path;
	int		**pipes;
	int		pipe1[2];
	int		pipe2[2];
}	t_data;

//path
void	split_path(t_data *data, int argc, char **argv, char **envp);
void	check_path(t_data *data, int argc, char **argv);
char	*exist_or_not(t_data *data, char *argv);
char	*split_argv(t_data *data, char *argv);

//utils
int		error_checking(int argc, char **argv);
void	free_twod(char **twod);
void	free_semua(t_data *data);

#endif