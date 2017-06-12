/*
** create_alias.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sun May 14 16:22:32 2017 Benjamin GAYMAY
** Last update Sat May 20 18:55:37 2017 Benjamin GAYMAY
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "my_printf.h"
#include "use_array.h"
#include "minishell2.h"

static int	put_tmp(char **tab, char **new, int f, int i)
{
  char		*tmp;

  if ((tmp = strdup(tab[f])) == NULL)
    return (ERROR);
  if (f == 1)
    new[i] = tmp;
  else if (f == 2)
    new[i] = my_pimp_malloc_strcat(new[i], tmp, '\t');
  else
    new[i] = my_pimp_malloc_strcat(new[i], tmp, ' ');
  if (f != 1)
    free(tmp);
  return (SUCCESS);
}

int		add_one_line(char **old, char **tab)
{
  char		**new;
  int		i;
  int		f;

  if ((new = my_calloc(tab_len(old) + tab_len(tab), sizeof(*new))) == NULL)
    return (ERROR);
  i = -1;
  while (old[++i] != NULL)
    new[i] = old[i];
  f = 0;
  while (tab[++f] != NULL)
    if (put_tmp(tab, new, f, i) == ERROR)
      return (ERROR);
  new[i + 1] = NULL;
  get_alias(SAVE, new);
  return (SUCCESS);
}

int		replace_alias(char **alias, char **tab)
{
  int		i;
  int		f;
  int		len;

  i = 0;
  while (alias[i] != NULL)
    {
      if (my_strncmp(alias[i], tab[1], (len = my_strlen(tab[1]))) == SAME &&
	  alias[i][len] == '\t')
	break ;
      ++i;
    }
  free(alias[i]);
  f = 0;
  while (tab[++f] != NULL)
    if (put_tmp(tab, alias, f, i) == ERROR)
      return (ERROR);
  return (SUCCESS);
}

char		*get_alias_line(char **alias, char *line)
{
  int		i;
  int		len;

  i = 0;
  while (alias[i] != NULL)
    {
      if (my_strncmp(alias[i], line, (len = my_strlen(line))) == SAME &&
	  alias[i][len] == '\t')
	break ;
      ++i;
    }
  return (alias[i] != NULL ? &alias[i][len + 1] : NULL);
}

int		add_alias(char **tab)
{
  char		**alias;
  char		*tmp;

  alias = ascii_order(get_alias(GET, NULL));
  if (tab[1] == NULL)
    my_showtab(alias);
  else if (tab[2] == NULL && (tmp = get_alias_line(alias, tab[1])) != NULL)
    my_printf("%s\n", tmp);
  else if (tab[2] != NULL && my_strcmp(tab[1], "alias") == SAME)
    return (my_putstr_failure("alias: Too dangerous to alias that.\n", 1));
  else if (tab[2] != NULL)
    {
      if (get_alias_line(alias, tab[1]) != NULL)
	{
	  if ((replace_alias(alias, tab)) == ERROR)
	    return (ERROR);
	}
      else if (add_one_line(alias, tab) == ERROR)
	return (ERROR);
    }
  return (SUCCESS);
}
