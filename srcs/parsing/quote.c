/*
** quote.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed May 17 23:46:41 2017 Benjamin GAYMAY
** Last update Sat May 20 19:14:25 2017 Benjamin GAYMAY
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "minishell2.h"

static char	*first_quote(int *first_line, int *nb_quote, int i, char **tab)
{
  char		*tmp;

  *first_line = i;
  tmp = my_malloc_strcat("\0", tab[i]);
  if (my_strlen(tab[i]) > 1 && tab[i][my_strlen(tab[i]) - 1] == '"')
    ++(*nb_quote);
  ++(*nb_quote);
  return (tmp);
}

static char	*last_quote(char *tmp, int *nb_quote, int *i, char **tab)
{
  tmp = my_pimp_malloc_strcat(tmp, tab[*i], ' ');
  delete_line(tab, tab[*i]);
  --(*i);
  ++(*nb_quote);
  return (tmp);
}

static char	*middle_quote(char *tmp, int *i, char **tab)
{
  tmp = my_pimp_malloc_strcat(tmp, tab[*i], ' ');
  delete_line(tab, tab[*i]);
  --(*i);
  return (tmp);
}

char		**concat_quote(char **tab)
{
  int		i;
  int		nb_quote;
  int		first_line;
  char		*tmp;

  i = -1;
  nb_quote = 0;
  tmp = NULL;
  while (tab[++i])
    {
      if (tab[i][0] == '"' && nb_quote % 2 == 0)
	tmp = first_quote(&first_line, &nb_quote, i, tab);
      else if (tab[i][my_strlen(tab[i]) - 1] == '"' && nb_quote % 2 != 0)
	tmp = last_quote(tmp, &nb_quote, &i, tab);
      else if (nb_quote % 2 != 0)
	tmp = middle_quote(tmp, &i, tab);
    }
  if (tmp != NULL)
    {
      free(tab[first_line]);
      tab[first_line] = delete_str(clear_str(tmp, ' '), '"');
    }
  return (tab);
}

char		*get_short_cmd(int *i, char *command, char separator)
{
  char		*cmd;
  int		nb_quote;
  int		f;

  nb_quote = 0;
  f = 0;
  if ((cmd = my_calloc(my_strlen(command) + 1, sizeof(char))) == NULL)
    return (NULL);
  while (command[*i] != '\0')
    {
      if (command[*i] == separator && nb_quote % 2 == 0)
	break ;
      if (command[*i] == '"')
	++nb_quote;
      cmd[f++] = command[(*i)++];
    }
  if (command[*i] != '\0')
    ++(*i);
  return (cmd);
}
