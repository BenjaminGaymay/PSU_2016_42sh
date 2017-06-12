/*
** pipe.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Fri Mar 31 13:09:21 2017 Benjamin GAYMAY
** Last update Sat May 20 19:11:42 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "minishell2.h"

static char	**get_pipe_cmd(char **tab, char *separator)
{
  static int	i;
  static int	save;
  int		f;
  char		**new_tab;

  if (i == 0)
    save = tab_len(tab);
  if (i >= save)
    {
      i = 0;
      return (NULL);
    }
  if ((new_tab = my_calloc(save + 1, sizeof(char *))) == NULL)
    return (NULL);
  f = 0;
  while (tab[i] != NULL && my_strcmp(tab[i], separator) != SAME)
    new_tab[f++] = my_malloc_strcpy(tab[i++]);
  if (tab[i] != NULL)
    i += 1;
  new_tab[f] = NULL;
  return (new_tab);
}

static int	dup_pipe(int i, int fdpipe[2])
{
  if (dup2(fdpipe[i], i) == FD_ERROR)
    return (ERROR);
  close(fdpipe[0]);
  close(fdpipe[1]);
  return (SUCCESS);
}

static int	exec_one_pipe(int fdpipe[2], char **envp, char **tab)
{
  int		ret;
  int		pid;

  if (pipe(fdpipe) == FD_ERROR)
    return (ERROR);
  if ((pid = fork()) == FD_ERROR)
    return (ERROR);
  if (pid == 0)
    {
      if (dup_pipe(OUT, fdpipe) == ERROR)
	return (ERROR);
      if (is_builtin(tab[0], QUIET) == SUCCESS)
	pid = 1;
      check_exit(envp, tab, ret, &ret);
      exit(pid == 1 && ret == SUCCESS ? 141 : ret);
    }
  if (dup_pipe(IN, fdpipe) == ERROR)
    return (ERROR);
  free_array(tab);
  return (SUCCESS);
}

static int	get_return(int pipe_nb, int ret)
{
  int		new_ret;
  int		save_ret;

  save_ret = ret;
  while (--pipe_nb != 0)
    {
      wait(&new_ret);
      new_ret = WEXITSTATUS(new_ret);
      if (save_ret != 0 && new_ret == 141)
	ret = save_ret;
      if ((new_ret == 1 || new_ret == 2 || new_ret == 141)
	  && ret == 0)
	ret = new_ret;
    }
  return (ret);
}

int		exec_pipe(char **new_envp, char **tab, int my_exit, int *ret)
{
  int		pipe_nb;
  int		fdpipe[2];
  char		**new_tab;

  pipe_nb = 0;
  while ((new_tab = get_pipe_cmd(tab, "|")) != NULL)
    {
      if (check_pipe_redir(new_tab, ret, pipe_nb, nb_pipe(tab)) == FAILURE)
	{
	  while ((new_tab = get_pipe_cmd(tab, "|")) != NULL)
	    free_array(new_tab);
	  pipe_nb = (pipe_nb != 0 ? get_return(++pipe_nb, *ret) : pipe_nb);
	  return (my_exit);
	}
      if (pipe_nb != nb_pipe(tab))
	{
	  if (exec_one_pipe(fdpipe, new_envp, new_tab) == ERROR)
	    return (ERROR);
	}
      else
	my_exit = check_exit(new_envp, new_tab, my_exit, ret);
      ++pipe_nb;
    }
  *ret = get_return(pipe_nb, *ret);
  return (my_exit);
}
