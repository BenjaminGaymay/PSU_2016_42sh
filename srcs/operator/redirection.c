/*
** redirection.c for minishell2 in /home/benjamin.g/delivery/PSU_2016_minishell2
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Mon Mar 27 17:26:02 2017 Benjamin GAYMAY
** Last update Sat May 20 19:13:16 2017 Benjamin GAYMAY
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"
#include "chained_list.h"
#include "get_next_line.h"

static int	double_left(char *end)
{
  char		*s;
  int		fdpipe[2];

  pipe(fdpipe);
  my_putstr(isatty(0) == 1 ? "? " : "");
  while ((s = get_next_line(0)) != NULL && my_strcmp(s, end) != SAME)
    {
      my_putstr(isatty(0) == 1 ? "? " : "");
      write(fdpipe[1], s, my_strlen(s));
      write(fdpipe[1], "\n", 1);
      free(s);
    }
  if (s != NULL && my_strcmp(s, end) == SAME)
    free(s);
  close(fdpipe[1]);
  return (fdpipe[0]);
}

static int	my_access(mode_t flags, char *path, const int i)
{
  if (i == IN)
    {
      if (access(path, F_OK) == -1)
	my_fprintf("%s: No such file or directory.\n", path);
      else if (access(path, R_OK) == -1)
	my_fprintf("%s: Permission denied.\n", path);
      else
	return (open(path, flags, 0644));
    }
  else
    {
      if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
	my_fprintf("%s: Permission denied.\n", path);
      else if (access(path, F_OK) == 0 && check_is_dir(path) == SUCCESS)
	my_fprintf("%s: Is a directory.\n", path);
      else
	return (open(path, flags, 0644));
    }
  return (FD_ERROR);
}

static int	input_fd(char **tab)
{
  int		i;
  int		i_fd;

  i = 0;
  i_fd = 0;
  while (tab[i] != NULL)
    {
      if (my_strcmp(tab[i], "<") == 0 || my_strcmp(tab[i], "<<") == SAME)
	{
	  if (tab[i + 1] != NULL && my_strcmp(tab[i], "<") == SAME)
	    i_fd = my_access((O_RDONLY), tab[i + 1], IN);
	  else if (tab[i + 1] != NULL && my_strcmp(tab[i], "<<") == SAME)
	    i_fd = double_left(tab[i + 1]);
	  i = clear_tab(tab, i);
	}
      ++i;
    }
  return (i_fd < 0 ? FD_ERROR : i_fd);
}

static int	output_fd(char **tab)
{
  int		i;
  int		o_fd;

  i = 0;
  o_fd = 1;
  while (tab[i] != NULL)
    {
      if (my_strcmp(tab[i], ">") == SAME || my_strcmp(tab[i], ">>") == SAME)
	{
	  if (tab[i + 1] != NULL && my_strcmp(tab[i], ">") == SAME)
	    o_fd = my_access((O_CREAT | O_WRONLY | O_TRUNC), tab[i + 1], OUT);
	  else if (tab[i + 1] != NULL && my_strcmp(tab[i], ">>") == SAME)
	    o_fd = my_access((O_CREAT | O_WRONLY | O_APPEND), tab[i + 1], OUT);
	  i = clear_tab(tab, i);
	}
      ++i;
    }
  return (o_fd < 0 ? FD_ERROR : o_fd);
}

int		check_redirect(char **tab, int *ret)
{
  int		i_fd;
  int		o_fd;

  if (tab_len(tab) == 0)
    return (FAILURE);
  if (invalid_cmd(tab) == FAILURE ||
      (i_fd = input_fd(tab)) == -1 || (o_fd = output_fd(tab)) == -1)
    return (*ret = FAILURE);
  if (tab_len(tab) == 0 && *ret != -1)
    return (my_putstr_failure("Invalid null command.\n", (*ret = FAILURE)));
  if (i_fd != IN && dup2(i_fd, IN) == FD_ERROR)
    return (ERROR);
  if (o_fd != OUT && dup2(o_fd, OUT) == FD_ERROR)
    return (ERROR);
  if (o_fd != OUT)
    close(o_fd);
  if (i_fd != IN)
    close(i_fd);
  return (*ret = SUCCESS);
}
