/*
** alias.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Fri May 12 09:05:53 2017 Benjamin GAYMAY
** Last update Sat May 20 18:54:06 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "my_printf.h"
#include "my_fprintf.h"
#include "use_array.h"
#include "minishell2.h"

char		**create_new_tab(char **old, char **tmp)
{
  char		**new;
  int		i;
  int		f;

  if ((new = my_calloc(tab_len(old) + tab_len(tmp), sizeof(*new))) == NULL)
    return (NULL);
  i = -1;
  while (tmp[++i] != NULL)
    new[i] = tmp[i];
  f = 0;
  while (old[++f] != NULL)
    new[i++] = old[f];
  new[i] = NULL;
  free(old[0]);
  free(old);
  free(tmp);
  return (new);
}

void		delete_alias(char **alias, char *line)
{
  int		i;
  int		len;

  i = 0;
  while (alias[i] != NULL)
    {
      if (my_strncmp(alias[i], line, (len = my_strlen(line))) == SAME &&
	  alias[i][len] == '\t')
	{
	  delete_line(alias, alias[i]);
	  break ;
	}
      ++i;
    }
}
char		**put_one_alias(char **tab, char **alias)
{
  char		**new;
  char		*alias_line;

  if ((alias_line = strdup(get_alias_line(alias, tab[0]))) == NULL)
    return (NULL);
  delete_alias(alias, tab[0]);
  if ((new = create_array(alias_line, ' ')) == NULL)
    return (NULL);
  if ((new = create_new_tab(tab, new)) == NULL)
    return (NULL);
  return (new);
}

char		**put_alias(char **tab, char **alias)
{
  char		*alias_line;
  char		**copy_alias;
  int		len;

  if (is_inhib(NULL, GET) == 1)
    return (tab);
  if ((copy_alias = copy_array(alias)) == NULL)
    return (NULL);
  len = tab_len(alias) + 1;
  while (--len != 0 &&
	 (alias_line = get_alias_line(copy_alias, tab[0])) != NULL)
    if ((tab = put_one_alias(tab, copy_alias)) == NULL)
      return (NULL);
  free_array(copy_alias);
  return (tab);
}

int		remove_alias(char **tab)
{
  char		**alias;
  int		i;

  alias = get_alias(GET, NULL);
  if (tab[1] == NULL)
    return (my_putstr_failure("unalias: Too few arguments.\n", FAILURE));
  else
    {
      i = 1;
      while (tab[i] != NULL)
	{
	  delete_alias(alias, tab[i]);
	  ++i;
	}
    }
  return (SUCCESS);
}
