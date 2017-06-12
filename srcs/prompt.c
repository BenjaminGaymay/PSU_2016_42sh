/*
** prompt.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Tue Mar 21 20:06:35 2017 Benjamin GAYMAY
** Last update Sat May 20 19:09:11 2017 Benjamin GAYMAY
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "my_printf.h"
#include "minishell2.h"
#include "get_next_line.h"
#include "macro.h"

static char	*the_return(char *str, int len)
{
  int		j;

  j = 0;
  while (len > 0)
    {
      if (str[len] == '/')
	j++;
      if (j == 2 || len <= 1)
	return (str[len] == '/' ? &str[len + 1] : &str[len]);
      len--;
    }
  return (NULL);
}

int		count_slash(char *str)
{
  int		i;
  int		slash;

  slash = 0;
  i = 0;
  while (str[i])
    {
      if (str[i] == '/')
	++slash;
      ++i;
    }
  return (slash);
}

static int	pimped_prompt()
{
  char		*prompt;

  if ((prompt = my_ps2(GET, NULL)) == NULL)
    return (ERROR);
  write(1, prompt, my_strlen(prompt));
  return (SUCCESS);
}

int		pwd_prompt()
{
  char		*s;
  char		*pwd;
  int		lenght;

  if (pimped_prompt() == SUCCESS)
    return (SUCCESS);
  pwd = NULL;
  s = getcwd(pwd, 0);
  lenght = my_strlen(s);
  if ((count_slash(s)) <= 2)
    my_putchar('/');
  my_printf("%s> ", the_return(s, lenght));
  free(s);
  return (SUCCESS);
}

char		*prompt(int *ret)
{
  char		*command_list;

  if (isatty(0) == 1)
    pwd_prompt();
  if ((command_list = get_next_line(0)) == NULL)
    {
      my_putstr(isatty(0) == 1 ? "exit\n" : "\0");
      return (NULL);
    }
  if ((command_list = super_str(command_list, 0, 0)) == NULL)
    {
      *ret = ERROR;
      return (NULL);
    }
  command_list = check_command(command_list);
  if (my_strcmp(command_list, "\\") == 0)
    command_list = new_cmd(command_list);
  return (command_list);
}
