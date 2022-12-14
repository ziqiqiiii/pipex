/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:42:21 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 13:23:20 by tzi-qi           ###   ########.fr       */
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

// ncmd is the number of commands

// envp is split envp 
// path is the path for cmds

// pipe1 is pipe

//argv_two is argv[2]
//argv_three is argv[3]

typedef struct sdata
{
	int		f1;
	int		f2;
	int		ncmd;
	char	**envp;
	char	**path;
	int		pipe1[2];
}	t_data;

//path
void	split_path(t_data *data, int argc, char **argv, char **envp);
void	complete_path(char **split, t_data *data);
void	check_path(t_data *data, int argc, char **argv);
char	*exist_or_not(t_data *data, char *argv);
char	*split_argv(t_data *data, char *argv);

//utils
void	init_data(int argc, char **argv, char **envp, t_data *data);
int		error_checking(int argc, char **argv);
void	free_twod(char **twod);
void	free_semua(t_data *data);

//pipex
void	pipex(char **argv, t_data *data, char **envp);
void	eldest_child(int f1, char *argv, t_data *data, char **envp);
void	youngest(int f2, char *argv, t_data *data, char **envp);

//ft_utlis
int		ft_pipe(int p[2]);
int		ft_open(const char *file, int flags, int permission);
int		ft_fork(void);
int		ft_close(int fd);

#endif