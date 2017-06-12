/*
** inhib.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
** 
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
** 
** Started on  Tue May 16 11:18:13 2017 benoit pingris
** Last update Tue May 16 11:29:30 2017 benoit pingris
*/

#include "macro.h"

int		is_inhib(char *cmd, int mode)
{
  static int	status;

  if (mode == SAVE)
    {
      if (cmd[0] == '\\')
	status = 1;
      else
	status = 0;
    }
  return (status);
}
