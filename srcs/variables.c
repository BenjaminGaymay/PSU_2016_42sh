/*
** variables.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed Apr 19 09:38:54 2017 Benjamin GAYMAY
** Last update Sat May 20 19:19:16 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"

static char	*get_var(char *old)
{
  char		*var;
  int		i;
  int		f;
  int		size;

  i = -1;
  size = 0;
  while (old[++i] != '\0' && old[i] != '$')
    ++size;
  if ((var = my_calloc(size + 2, sizeof(char))) == NULL)
    return (NULL);
  i = -1;
  f = -1;
  while (old[++i] != '\0' && old[i] != '$')
    var[++f] = old[i];
  var[++f] = '=';
  return (var);
}

static char	*get_var_in_list(char *var)
{
  char		*val;
  char		**envp;
  char		**var_list;

  envp = my_get_env(GET, NULL);
  var_list = get_var_tab(GET, NULL);
  if (my_strcmp(var, "?=") == SAME)
    {
      free(var);
      return (give_ret_value(GET, 0));
    }
  if ((val = get_great_var(var_list, envp, var)) == NULL)
    {
      free(var);
      return (NULL);
    }
  else
    return (val);
}

static char	*give_me_var(char **tab, int *i, int last, char *line)
{
  char		*var;
  char		*save_var;

  if ((var = get_var(&tab[*i][last])) == NULL)
    *i = ERROR;
  else if ((save_var = my_malloc_strncpy(var, my_strlen(var) - 1)) == NULL)
    *i = ERROR;
  else if ((var = get_var_in_list(var)) == NULL)
    {
      my_fprintf("%s: Undefined variable.\n", save_var);
      if (line != NULL)
	free(line);
      *i = FAILURE;
    }
  else
    {
      free(save_var);
      return (var);
    }
  free(save_var);
  return (NULL);
}

static char	*get_my_new_line(char *tab_line, int last,
				 char *line, char *var)
{
  if (line == NULL)
    {
      if ((line = my_calloc(my_strlen(tab_line), sizeof(char))) == NULL)
	return (NULL);
      line[0] = '\0';
      line = my_strncat(line, tab_line, last - 1);
    }
  if ((line = my_realloc(line, my_strlen(var) + my_strlen(tab_line))) == NULL)
    return (NULL);
  line = my_strcat(line, var);
  free(var);
  return (line);
}

int		change_var(char **tab, int i, int f)
{
  int		last;
  char		*var;
  char		*line;

  while (tab[++i])
    {
      last = -1;
      line = NULL;
      while (tab[i][++last] != '\0')
	{
	  if ((f = my_strstr(&tab[i][last], "$")) != -1 &&
	      tab[i][last + f] != '\0' && tab[i][last + f] != '$')
	    {
	      if ((var = give_me_var(tab, &i, (last += f), line)) == NULL)
		return (free_array_return(tab, i));
	      if ((line = get_my_new_line(tab[i], last, line, var)) == NULL)
		return (free_array_return(tab, ERROR));
	    }
	}
      if (line != NULL)
	replace_line(tab, i, line);
    }
  return (SUCCESS);
}
