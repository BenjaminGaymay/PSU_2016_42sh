/*
** is_redir.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Tue May  9 14:07:04 2017 benoit pingris
** Last update Sat May 20 19:04:42 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "macro.h"
#include "minishell2.h"

int		look_redir(char *s)
{
  if (s == NULL)
    return (SUCCESS);
  if (my_strcmp(s, "<") == SAME ||
      my_strcmp(s, "<<") == SAME ||
      my_strcmp(s, ">") == SAME ||
      my_strcmp(s, ">>") == SAME)
    return (SUCCESS);
  return (FAILURE);
}
