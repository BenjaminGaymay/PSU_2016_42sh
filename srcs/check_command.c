/*
** check_command.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sun May 14 16:16:45 2017 Benjamin GAYMAY
** Last update Sat May 20 19:02:09 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "stdlib.h"
#include "back.h"
#include "my.h"
#include "macro.h"
#include "get_next_line.h"
#include "my_fprintf.h"

int		put_error(int status, char *command)
{
  int		ret;

  if (status == SEGFAULT || status == WSEGV)
    ret = my_putstr_failure("Segmentation fault", SEGFAULT);
  else if (status == FLOATING || status == WFLOAT)
    ret = my_putstr_failure("Floating exception", FLOATING);
  else if (status == ABORT || status == WABORT)
    ret = my_putstr_failure("Abort", ABORT);
  else if (WEXITSTATUS(status) == BINARY_ERROR)
    {
      my_fprintf("%s: Exec format error. ", command);
      return (my_putstr_failure("Binary file not executable.\n", FAILURE));
    }
  else
    return (SUCCESS);
  if (WCOREDUMP(status))
    my_fprintf(" (core dumped)");
  my_fprintf("\n");
  return (ret);
}

int		is_path(char *name)
{
  int		i;

  i = 0;
  while (name[i])
    {
      if (name[i] == '/')
	return (SUCCESS);
      ++i;
    }
  return (FAILURE);
}

char		*new_cmd(char *old)
{
  char		*s;

  free(old);
  write(1, "? ", 2);
  if ((s = get_next_line(0)) == NULL)
    return (NULL);
  return (s);
}

char		*check_command(char *s)
{
  int		i;

  if (my_strlen(s) == 0)
    return (s);
  i = 0;
  while (s[i])
    {
      if (s[i] == '\'' || s[i] == '"')
	{
	  s[i] = '"';
	  break ;
	}
      ++i;
    }
  i = my_strlen(s) - 1;
  while (i != 0)
    {
      if (s[i] == '\'' || s[i] == '"')
	{
	  s[i] = '"';
	  break ;
	}
      --i;
    }
  return (s);
}
