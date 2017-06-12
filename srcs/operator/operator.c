/*
** operator.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Wed May 17 15:01:48 2017 benoit pingris
** Last update Sat May 20 19:11:15 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "minishell2.h"
#include "chained_list.h"

int		launch_pipe(char **new_envp, char **tab, int *ret, int *i)
{
  int		my_exit;
  char		**new;

  new = NULL;
  my_exit = -1;
  new = copy_op_tab(&tab[*i], "||", "&&");
  if ((my_exit = exec_pipe(new_envp, new, my_exit, ret)) == ERROR)
    return (ERROR);
  if (new != NULL)
    {
      *i += tab_len(new) - 1;
      free(new);
    }
  return (my_exit);
}

int		do_operation(char **new_envp, char **tab, int *i, int *ret)
{
  int		pipe;
  int		my_exit;
  char		**new;

  my_exit = -1;
  new = NULL;
  if ((pipe = nb_pipe(&tab[++*i])) != -1 && pipe != 0)
    my_exit = launch_pipe(new_envp, tab, ret, i);
  else
    {
      new = copy_first_op(&tab[*i]);
      my_exit = check_exit(new_envp, copy_array(&new[0]), my_exit, ret);
      if (new != NULL)
	{
	  *i += tab_len(new) - 1;
	  free(new);
	}
    }
  return (my_exit);

}

int		do_first_op(char **new_envp, char **tab, int *i, int *ret)
{
  int		my_exit;
  char		**new;

  my_exit = -1;
  new = NULL;
  new = copy_first_op(&tab[*i]);
  if (new[0] != NULL)
    my_exit = check_exit(new_envp, copy_array(new), my_exit, ret);
  if (new != NULL)
    {
      *i += tab_len(new) - 1;
      free(new);
    }
  return (my_exit);
}

int		exec_op(char **new_envp, char **tab, int my_exit, int *ret)
{
  t_op		op;

  op.i = -1;
  op.rep = -1;
  if (my_dup(GET) == FD_ERROR)
    return (ERROR);
  while (tab[++op.i] != NULL && my_exit == -1 && my_dup(SAVE) == SUCCESS)
    {
      if ((op.pipe = nb_pipe(&tab[op.i])) != -1 && op.pipe != 0)
	{
	  if ((my_exit = launch_pipe(new_envp, tab, ret, &op.i)) == ERROR)
	    return (ERROR);
	}
      else if (++op.rep == 0)
	my_exit = do_first_op(new_envp, tab, &op.i, ret);
      else if (my_strcmp(tab[op.i], "&&") == SAME && *ret == 0)
	my_exit = do_operation(new_envp, tab, &op.i, ret);
      else if (my_strcmp(tab[op.i], "||") == SAME && CHECK_RET(*ret) == 1)
	my_exit = do_operation(new_envp, tab, &op.i, ret);
      else if (my_strcmp(tab[op.i], "&&") != SAME && *ret == 0)
	break ;
      if (my_dup(GET) == FD_ERROR)
	return (ERROR);
    }
  return (my_exit);
}
