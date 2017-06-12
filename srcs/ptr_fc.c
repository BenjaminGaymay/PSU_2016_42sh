/*
** ptr_fc.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Wed May 17 11:51:33 2017 benoit pingris
** Last update Sat May 20 18:35:01 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"

static int	(*exec_builtin[15])(char **envp, char **tab, int *ret) =
{
  exec_alias,
  exec_built,
  exec_cd,
  exec_cd,
  exec_echo,
  exec_ps1,
  exec_repeat,
  exec_set,
  exec_setenv,
  exec_unalias,
  exec_unset,
  exec_unsetenv,
  exec_where,
  exec_which
};

int		exec_final_command(char **envp, char **tab, int *ret)
{
  int		i;
  int		nb_builtins;

  i = get_builtins_nb(tab[0]);
  nb_builtins = count_builtins();
  if (i >= nb_builtins)
    {
      if ((tab = my_inhib(tab)) == NULL)
	return (ERROR);
      if ((*ret = parent(envp, tab)) == ERROR)
	return (ERROR);
    }
  else
    if (exec_builtin[i](envp, tab, ret) == ERROR)
      return (ERROR);
  return (SUCCESS);
}

char		*get_great_var(char **var_list, char **envp, char *var)
{
  int		i;
  int		len;

  i = -1;
  len = my_strlen(var);
  while (var_list[++i] != NULL)
    if (my_strncmp(var_list[i], var, len - 1) == SAME)
      {
	free(var);
	return (my_malloc_strcpy(&var_list[i][len]));
      }
  i = -1;
  while (envp[++i] != NULL)
    if (my_strncmp(envp[i], var, len) == SAME)
      {
	free(var);
	return (my_malloc_strcpy(&envp[i][len]));
      }
  return (NULL);
}
