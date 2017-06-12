/*
** quotes.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Wed May 17 16:11:56 2017 benoit pingris
** Last update Sat May 20 13:01:56 2017 Benjamin GAYMAY
*/

#include "macro.h"
#include "my_fprintf.h"

int	check_quote(char *cmd, int *ret)
{
  int	i;
  int	d_quote;

  i = 0;
  d_quote = 0;
  while (cmd[i])
    {
      if (cmd[i] == '"')
	++d_quote;
      ++i;
    }
  if (d_quote % 2 != 0)
    {
      *ret = 1;
      my_fprintf("Unmatched '\"'.\n");
      return (ERROR);
    }
  return (SUCCESS);
}
