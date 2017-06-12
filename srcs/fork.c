/*
** fork.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh/srcs
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue May  9 11:17:03 2017 Benjamin GAYMAY
** Last update Sat May 20 19:02:24 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "macro.h"
#include "minishell2.h"

int		child(char **envp, char *command, char **tab)
{
  execve(command, tab, envp);
  exit(BINARY_ERROR);
}

int		father(char *command, char **tab)
{
  int		status;
  int		error;

  status = 0;
  wait(&status);
  free(command);
  if ((error = put_error(status, tab[0])) != SUCCESS)
    return (error);
  else
    return (WEXITSTATUS(status));
}
