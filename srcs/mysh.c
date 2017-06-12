/*
** mysh.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 20:04:59 2017 Benjamin GAYMAY
** Last update Sat May 20 19:04:31 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"

char		**get_cmd(char *command, const char separator)
{
  static int	i;
  static int	save;
  char		**tab;

  if (i == 0)
    save = my_strlen(command);
  if (i >= save)
    {
      i = 0;
      return (NULL);
    }
  if ((command = get_short_cmd(&i, command, separator)) == NULL)
    return (NULL);
  if ((tab = create_array(command, ' ')) == NULL)
    return (NULL);
  return (concat_quote(tab));
}

int		check_exit(char **new_envp, char **tab,
			   int my_var_exit, int *ret)
{
  int		redirect;

  if ((redirect = check_redirect(tab, ret)) == SUCCESS)
    {
      new_envp = my_get_env(GET, NULL);
      if (my_strcmp(tab[0], "exit") == SAME)
	{
	  if ((*ret = my_exit(tab)) == SUCCESS)
	    {
	      *ret = (tab[1] == NULL ? SUCCESS : my_getnbr(tab[1]));
	      my_var_exit = *ret;
	    }
	}
      else if (exec_final_command(new_envp, tab, ret) == ERROR)
	return (ERROR);
    }
  free_array(tab);
  if (redirect == ERROR)
    return (ERROR);
  return (my_var_exit);
}

int		check_my_tab(char **new_envp, char **tab,
			     int my_exit, int *ret)
{
  my_dup(SAVE);
  if (nb_op(tab) == 0)
    my_exit = check_exit(new_envp, tab, my_exit, ret);
  else if (nb_op(tab) != -1)
    {
      if ((my_exit = exec_op(new_envp, tab, my_exit, ret)) == ERROR)
	return (ERROR);
      my_dup(SAVE);
      free_array(tab);
    }
  else
    {
      *ret = FAILURE;
      if (is_redir(tab, ret, 0) == SUCCESS)
	{
	  my_fprintf("Invalid null command.\n");
	  free_array(tab);
	}
    }
  if (my_dup(GET) == FD_ERROR)
    return (ERROR);
  return (my_exit);
}

int		treat_cmd(char *command, int *ret,
			  char **new_envp, int *my_exit)
{
  char		**tab;

  while ((tab = get_cmd(command, ';')) != NULL)
    {
      is_inhib(tab[0], SAVE);
      if ((tab = put_alias(tab, get_alias(GET, NULL))) == NULL)
	return (ERROR);
      if ((*ret = change_var(tab, -1, 0)) != SUCCESS)
	{
	  if (*ret == ERROR)
	    return (ERROR);
	  while ((tab = get_cmd(command, ';')) != NULL)
	    free_array(tab);
	  break ;
	}
      if ((*my_exit = check_my_tab(new_envp, tab, *my_exit, ret)) == ERROR)
	return (ERROR);
      give_ret_value(SAVE, *ret);
    }
  return (SUCCESS);
}

int		start_mysh(char **new_envp, int ret, int my_exit)
{
  char		*command;

  give_ret_value(SAVE, ret);
  while (my_exit == CONTINUE)
    {
      if ((command = prompt(&ret)) == NULL)
	return (ret);
      if (check_quote(command, &ret) == SUCCESS)
	{
	  if ((ret = get_redirect_error(command)) == SUCCESS)
	    {
	      if (treat_cmd(command, &ret, new_envp, &my_exit) == ERROR)
		return (ERROR);
	    }
	  else if (ret == ERROR)
	    return (ERROR);
	}
      give_ret_value(SAVE, ret);
      free(command);
    }
  my_putstr(isatty(0) == 1 ? "exit\n" : "\0");
  return (ret);
}
