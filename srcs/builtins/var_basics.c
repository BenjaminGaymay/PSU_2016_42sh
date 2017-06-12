/*
** var_basics.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sat May 20 18:22:54 2017 Benjamin GAYMAY
** Last update Sat May 20 18:24:17 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "macro.h"
#include "use_array.h"
#include "minishell2.h"

char		**realloc_var(char **old, int size)
{
  char		**new;
  int		i;

  if (old == NULL)
    {
      if ((new = my_calloc(size, sizeof(*new))) == NULL)
	return (NULL);
      new[0] = NULL;
    }
  else
    {
      if ((new = my_calloc(size + tab_len(old), sizeof(*new))) == NULL)
	return (NULL);
      i = -1;
      while (old[++i] != NULL)
	new[i] = old[i];
      new[i] = NULL;
    }
  return (new);
}

char		**get_var_tab(int save, char **tab)
{
  static char	**save_var;

  if (save == SAVE)
    {
      if (save_var != NULL)
	free(save_var);
      save_var = tab;
    }
  return (save_var);
}
