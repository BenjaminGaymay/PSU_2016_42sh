/*
** clear_str.c for clear_str in /home/benjamin.g
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Thu Jan 19 17:19:46 2017 Benjamin GAYMAY
** Last update Sat May 20 19:17:05 2017 Benjamin GAYMAY
*/

#include <stdlib.h>
#include "my.h"
#include "macro.h"
#include "minishell2.h"

char		*transform_char(char *str, char old, const char new)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == old)
	str[i] = new;
      ++i;
    }
  return (str);
}

char		*clear_str(char *str, const char separator)
{
  int		i;
  int		h;
  char		*new;

  h = 0;
  i = 0;
  if ((new = my_calloc(my_strlen(str) + 1, sizeof(char))) == NULL)
    return (NULL);
  while (str[i] == separator)
    ++i;
  while (str[i] != '\0')
    {
      if (str[i] == separator)
	new[h++] = separator;
      while (str[i] == separator)
	++i;
      if (str[i] != '\0')
	new[h++] = str[i++];
    }
  if (h > 0 && new[h - 1] == separator)
    new[h - 1] = '\0';
  free(str);
  return (new);
}

static int	get_sign(const char c, int *sign, int *f, char *clear)
{
  int		nb_sign;

  if (c == '>')
    nb_sign = 0;
  else if (c == '<')
    nb_sign = 1;
  else if (c == '|')
    nb_sign = 2;
  else if (c == '&')
    nb_sign = 3;
  else
    return (FAILURE);
  if (++sign[nb_sign] > 1)
    {
      clear[*f] = ' ';
      *f += 1;
      set_int_tab(sign, 1);
      sign[nb_sign] = 0;
    }
  return (SUCCESS);
}

static int	put_space(const int i, int *f, char *command, char *clear)
{
  if (i > 0 && command[i - 1] != ' ' && command[i - 1] != command[i])
    {
      clear[*f] = ' ';
      *f += 1;
    }
  clear[*f] = command[i];
  *f += 1;
  if (command[i + 1] != '\0'
      && command[i] != command[i + 1]
      && command[i + 1] != ' ')
    {
      clear[*f] = ' ';
      *f += 1;
    }
  return (i + 1);
}

char		*super_str(char *command, int i, int f)
{
  char		*clear;
  int		sign[4];

  if ((clear = my_calloc(my_strlen(command) * 3 + 1, sizeof(char))) == NULL)
    return (NULL);
  set_int_tab(sign, 1);
  if ((command = clear_str(transform_char(command, '\t', ' '), ' ')) == NULL)
    return (NULL);
  while (command[i] != '\0')
    {
      if (get_sign(command[i], sign, &f, clear) == SUCCESS)
	i = put_space(i, &f, command, clear);
      else if (command[i] != '\0')
	{
	  set_int_tab(sign, 1);
	  clear[f++] = command[i++];
	}
    }
  free(command);
  return (clear_str(clear, ' '));
}
