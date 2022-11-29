/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:15 by tzi-qi            #+#    #+#             */
/*   Updated: 2022/11/29 21:00:26 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

// f1 is fd for infile
// f2 is fd for outfile

// ncmd is the number of commands

// envp is split envp 
// path is the path for cmds

// pipe1 is pipe

// fd is to store previous fd

// if hd == 1, got here_doc
// else no here_doc

typedef struct sdata
{
	int		f1;
	int		f2;
	int		ncmd;
	char	**envp;
	char	**path;
	int		pipe1[2];
	int		fd;
	int		hd;
}	t_data;

//path
void	split_path(t_data *data, int argc, char **argv, char **envp);
void	complete_path(char **split, t_data *data);
void	check_path(t_data *data, int argc, char **argv);
char	*exist_or_not(t_data *data, char *argv);
char	*split_argv(t_data *data, char *argv);

//utils
void	init_data(int argc, char **argv, char **envp, t_data *data);
int		error_checking(t_data *data, int argc, char **argv);
void	free_twod(char **twod);
void	free_semua(t_data *data);

//pipex
void	pipex(int argc, char **argv, t_data *data, char **envp);
void	here_doc(t_data *data, char *limiter);

//children
void	eldest_child(int f1, char *argv, t_data *data, char **envp);
void	youngest(int f2, char *argv, t_data *data, char **envp);
void	middle_children(char *argv, t_data *data, char **envp, int i);
void	loop_mid(t_data *data, pid_t *children, char **argv, char **envp);

//ft_utlis
int		ft_pipe(int p[2]);
int		ft_open(const char *file, int flags, int permission);
int		ft_fork(void);
int		ft_close(int fd);

#endif