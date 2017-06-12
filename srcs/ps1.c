/*
** ps1.c for 42sh in /home/benoit.pingris/delivery/PSU/PSU_2016_42sh
**
** Made by benoit pingris
** Login   <benoit.pingris@epitech.net>
**
** Started on  Tue May 16 14:52:06 2017 benoit pingris
** Last update Sat May 20 19:15:42 2017 Benjamin GAYMAY
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my_fprintf.h"
#include "macro.h"
#include "my.h"

char		*my_ps2(int mode, char *s)
{
  static char	*pwd;

  if (mode == SAVE)
    pwd = s;
  else if (mode == GET)
    return (pwd);
  else
    free(pwd);
  return (NULL);
}

int		my_ps1()
{
  int		fd;
  char		*s;
  int		stop;

  stop = 0;
  if ((fd = open(".42shrc", O_RDONLY)) == -1)
    return (FAILURE);
  while (stop == 0 && (s = get_next_line(fd)) != NULL)
    {
      if (my_strncmp(s, "PS1=", 4) == SAME)
	{
	  my_ps2(SAVE, strdup(&s[4]));
	  stop = 1;
	}
      free(s);
    }
  close(fd);
  return (SUCCESS);
}

int		change_ps1(char *cmd)
{
  char		*s;

  s = my_malloc_strcat(cmd, " ");
  my_ps2(FREE, NULL);
  my_ps2(SAVE, s);
  return (SUCCESS);
}
