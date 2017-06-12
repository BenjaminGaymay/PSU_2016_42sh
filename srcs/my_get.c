/*
** my_get.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
** 
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
** 
** Started on  Wed May 17 12:00:43 2017 benoit pingris
** Last update Wed May 17 14:11:30 2017 benoit pingris
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "macro.h"
#include "my_fprintf.h"
#include "use_array.h"

char		*get_oldpwd(const int i, char *new)
{
  static char	*pwd;

  if (i == SAVE)
    {
      if (pwd != NULL)
	free(pwd);
      pwd = new;
    }
  else
    return (pwd);
  return (NULL);
}

char		*give_ret_value(const int i, int ret_value)
{
  static int	ret_save;

  if (i == SAVE)
    ret_save = ret_value;
  else
    return (my_itoa(ret_save));
  return (NULL);
}

char		**my_get_env(const int i, char **envp)
{
  static char	**save_envp;

  if (i == SAVE)
    {
      if (save_envp != NULL)
	free(save_envp);
      save_envp = envp;
    }
  else
    return (save_envp);
  return (NULL);
}

int		my_dup(int save_it)
{
  static int	save[2];

  if (save_it == SAVE)
    {
      save[0] = dup(0);
      save[1] = dup(1);
    }
  else if (save_it == GET)
    {
      if (dup2(save[0], 0) == FD_ERROR ||
	  dup2(save[1], 1) == FD_ERROR)
	return (FD_ERROR);
      if (save[0] != IN)
	close(save[0]);
      if (save[1] != OUT)
	close(save[1]);
    }
  return (SUCCESS);
}

char		**get_alias(const int i, char **new)
{
  static char	**alias;

  if (i == SAVE)
    {
      if (alias != NULL)
	free(alias);
      alias = new;
    }
  else
    return (alias);
  return (NULL);
}
