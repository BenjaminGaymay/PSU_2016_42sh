/*
** set.c for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Sat May 20 16:11:54 2017 Benjamin GAYMAY
** Last update Sat May 20 18:59:13 2017 Benjamin GAYMAY
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "back.h"
#include "macro.h"
#include "use_array.h"
#include "my_fprintf.h"
#include "minishell2.h"

static char	**get_var_info(char **tab, int *i)
{
  char		**var_info;

  if ((var_info = my_calloc(3, sizeof(*var_info))) == NULL)
    return (NULL);
  if (my_strstr(tab[*i], "=") != -1 && my_strcmp(tab[*i], "=") != SAME)
    {
      var_info[NAME] = strndup(tab[*i], my_strstr(tab[*i], "=") - 1);
      var_info[VAL] = strdup(&tab[*i][my_strstr(tab[*i], "=")]);
    }
  else if (my_strcmp(tab[*i], "=") != SAME && tab[*i + 1] != NULL &&
	   my_strcmp(tab[*i + 1], "=") == SAME)
    {
      var_info[NAME] = strdup(tab[*i]);
      var_info[VAL] = strdup(tab[*i + 2] == NULL ? "\0" : tab[*i + 2]);
      *i = (tab[*i + 2] == NULL ? *i + 1 : *i + 2);
    }
  else
    {
      var_info[NAME] = strdup(tab[*i]);
      var_info[VAL] = strdup("\0");
    }
  var_info[2] = NULL;
  return (var_info);
}

static int	check_var_name(char **var_info)
{
  if (!((var_info[NAME][0] >= 'a' && var_info[NAME][0] <= 'z') ||
	(var_info[NAME][0] >= 'A' && var_info[NAME][0] <= 'Z')))
    {
      my_fprintf("set: Variable name must begin with a letter.\n");
      free_array(var_info);
      return (FAILURE);
    }
  return (SUCCESS);
}

static char	**put_var_in_tab(char **var_list, char **new_list,
				 char **var_info)
{
  char		*tmp;
  char		*var_line;

  tmp = my_malloc_strcat("\t", var_info[VAL]);
  if (put_newtab(var_list, new_list, var_info[NAME], tmp) == 0)
    {
      var_line = my_malloc_strcat(var_info[NAME], tmp);
      new_list[tab_len(var_list)] = var_line;
      new_list[tab_len(var_list) + 1] = NULL;
    }
  free_array(var_info);
  free(tmp);
  return (new_list);
}

int		exec_set(char **envp, char **tab, int *ret)
{
  char		**var_list;
  char		**new_list;
  char		**var_info;
  int		i;

  (void)envp;
  if (tab_len(tab) == 1)
    my_showtab(ascii_order(get_var_tab(GET, NULL)));
  else
    {
      i = 0;
      while (tab[++i] != NULL)
	{
	  var_list = get_var_tab(GET, NULL);
	  if ((var_info = get_var_info(tab, &i)) == NULL)
	    return (ERROR);
	  if ((*ret = check_var_name(var_info)) == FAILURE)
	    return (FAILURE);
	  if ((new_list = realloc_var(var_list, 2)) == NULL)
	    return (ERROR);
	  get_var_tab(SAVE, put_var_in_tab(var_list, new_list, var_info));
	}
    }
  return (*ret = SUCCESS);
}

int		exec_unset(char **envp, char **tab, int *ret)
{
  char		**var_list;
  int		i;

  (void)envp;
  var_list = get_var_tab(GET, NULL);
  if (tab[1] == NULL)
    return (my_putstr_failure("unset: Too few arguments.\n", *ret = FAILURE));
  else
    {
      i = 1;
      while (tab[i] != NULL)
	{
	  delete_alias(var_list, tab[i]);
	  ++i;
	}
    }
  return (*ret = SUCCESS);
}
