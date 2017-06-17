/* -*- Mode: C; tab-width: 8 -*-
   Copyright © 1997 Jamie Zawinski <jwz@jwz.org>.
   All work and no play makes Jack a dull boy.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int
main (int argc, char **argv)
{
#if	0
  const char text[] = "All work and no play makes Jack a dull boy.  ";
#else	/* YUP */
  const char text[] = "Meddle not in the affairs of wizards for they are subtle and quick to anger.";
#endif	/* YUP */
  const char *head = text;
  char *b;
  char buf[10240];
  while ((b = fgets(buf, sizeof(buf)-1, stdin))) {
    const char *in = b;
    const char *out = b;
    while (*b) {
      if (*b == 010)
	strcpy (b-1, b+1);
      else
	b++;
    }
    b = buf;
    if (*b && b[strlen(b)-1] == '\n')
      b[strlen(b)-1] = 0;
    if (*b && b[strlen(b)-1] == '\r')
      b[strlen(b)-1] = 0;
    while(*in) {
      for (; *out && isspace(*out); out++)
	;
      if (out > in)
	fwrite(in, 1, out-in, stdout);
      in = out;
      while (1) {
	for (; *in && !isspace(*in); in++)
	  ;
	if (!in[0] ||
	    (isspace(in[0]) && !in[1]) ||
	    (isspace(in[0]) && isspace(in[1]) &&
	     !in[2]) ||
	    (isspace(in[0]) && isspace(in[1]) && isspace(in[3])))
	  break;
	while (isspace(*in))
	  in++;
      }
      {
	const char *out2 = out;
	while (out2 < in) {
	  const char *ohead;
	  int i = 0;
	  while (isspace(*head))
	    head++;
	  for (ohead = head; *ohead && !isspace(*ohead); ohead++)
	    i++;
	  if (in-out2 >= i) {
	    fwrite(head, 1, i, stdout);
	    out2 += i;
	    head += i;
	    while(isspace(*head) && out2 < in) {
	      fwrite(head++, 1, 1, stdout);
	      out2++;
	    }
	    if (!*head)
	      head = text;
	  }
	  else {
	    while (out2 < in)
	      {
		fwrite(" ", 1, 1, stdout);
		out2++;
	      }
	  }
	}
      }
      out = in;
    }
    fwrite("\n",1,1,stdout);
  }
  return 0;
}
