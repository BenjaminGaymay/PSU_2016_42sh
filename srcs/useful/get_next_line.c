/*
** get_next_line.c for get_next_line in /home/benjamin.g/delivery/CPE_2016_getnextline
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed Jan 11 09:47:43 2017 Benjamin GAYMAY
** Last update Wed May 10 12:04:46 2017 Benjamin GAYMAY
*/

#include <unistd.h>
#include <stdlib.h>
#include "minishell2.h"
#include "get_next_line.h"

char		get_next_char(const int fd)
{
  static char	buffer[READ_SIZE + 1];
  static int	size = 0;
  static int	i = 0;
  char		my_char;

  if (size == 0)
    {
      if ((size = read(fd, buffer, READ_SIZE)) == 0)
	return ('\0');
      i = 0;
    }
  my_char = buffer[i];
  i++;
  size--;
  return (my_char);
}

char	*my_realloc(char *str, int size)
{
  char	*new_str;
  int	i;

  i = 0;
  while (str[i] != '\0')
    ++i;
  if ((new_str = my_calloc((i + size), sizeof(*new_str))) == NULL)
    return (NULL);
  i = 0;
  while (str[i] != '\0')
    {
      new_str[i] = str[i];
      ++i;
    }
  free(str);
  return (new_str);
}

static char	*free_last_line(char *line)
{
  free(line);
  return (NULL);
}

char	*get_next_line(const int fd)
{
  char	*line;
  char	my_char;
  int	i;

  if ((line = my_calloc(READ_SIZE + 1, sizeof(*line))) == NULL)
    return (NULL);
  i = 0;
  while ((my_char = get_next_char(fd)) != '\0' && my_char != '\n')
    {
      line[i] = my_char;
      ++i;
      if (i % READ_SIZE == 0)
	{
	  line[i] = '\0';
	  if ((line = my_realloc(line, READ_SIZE + 1)) == NULL)
	    return (NULL);
	}
    }
  return (my_char == '\0' && line[0] == '\0' ? free_last_line(line) : line);
}
