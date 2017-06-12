/*
** copy_array.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2/back
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 19:02:15 2017 Benjamin GAYMAY
** Last update Sat May 20 18:51:50 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "use_array.h"
#include "minishell2.h"

char		**copy_array(char **old_array)
{
  char		**new_array;
  int		i;

  i = 0;
  while (old_array[i] != NULL)
    ++i;
  if ((new_array = my_calloc(i + 1, sizeof(char *))) == NULL)
    return (NULL);
  i = 0;
  while (old_array[i] != NULL)
    {
      new_array[i] = my_malloc_strcpy(old_array[i]);
      ++i;
    }
  new_array[i] = NULL;
  return (new_array);
}

int		tab_len(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i] != NULL);
  return (i);
}

int		free_array_return(char **array, const int ret)
{
  free_array(array);
  return (ret);
}
