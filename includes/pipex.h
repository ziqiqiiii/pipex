#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct sdata
{
    int     ncmd;
    char    **path;
    char    **cmd;
    int     **pipe;
    int     pipeline[2];
}   t_data;

//path
void    split_path(t_data *data, int argc, char **argv, char **envp);
void    free_semua(t_data *data, int f1, int f2);
void    free_2D(char **twod);


#endif