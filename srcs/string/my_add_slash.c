/*
** my_add_slash.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Fri Mar 24 15:09:25 2017 Benjamin GAYMAY
** Last update Sat May 20 19:17:25 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"

char		*my_add_slash(char *str)
{
  char		*tmp;

  if ((tmp = my_malloc_strcpy(str)) == NULL)
    return (NULL);
  free(str);
  if ((str = my_malloc_strcat(tmp, "/")) == NULL)
    return (NULL);
  free(tmp);
  return (str);
}
