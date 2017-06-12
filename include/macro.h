/*
** macro.h for 42sh in /home/benjamin.g/delivery/PSU_2016_42sh
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Wed May 10 12:50:33 2017 Benjamin GAYMAY
** Last update Sat May 20 19:11:17 2017 Benjamin GAYMAY
*/

#ifndef MACRO_H_
# define MACRO_H_

#  define QUIET 0
#  define WHICH 1
#  define WHERE 2

#  define SUCCESS 0
#  define FAILURE 1
#  define ERROR   84

#  define SAME 0

#  define SAVE 0
#  define GET  1
#  define FREE 2

#  define BINARY_ERROR 255

#  define FD_ERROR -1
#  define IN       0
#  define OUT      1

#  define PIPE_ERROR -1

#  define ABORT    134
#  define FLOATING 136
#  define SEGFAULT 139
#  define WABORT   9
#  define WFLOAT   8
#  define WSEGV    11

#  define CHILD 0

#  define CONTINUE -1
#  define STOP_CMD 2
#  define QUIT     0

#  define NAME 0
#  define VAL  1

#  define NEXT_IS_PIPE(str) (my_strcmp(str, "|") == SAME ||		\
			     my_strcmp(str, "||") == SAME ? SUCCESS : FAILURE)

#  define CHECK_RET(ret) (((ret) == 1 ||			\
			   (ret) == 2 ||			\
			   (ret) == 141) ? FAILURE : SUCCESS)

#endif /* !MACRO_H_ */
