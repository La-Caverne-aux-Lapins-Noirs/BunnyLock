/*
** *****************************************************************************
** Jason Brillante "Damdoshi" <jason.brillante@gmail.com>
** Hanged Bunny Studio 2014-2019
**
** - Bunny Lock -
**
** *****************************************************************************
*/

#include		"block.h"

void			write_letters(t_bunny_window		*win,
				      const char		*str,
				      const t_bunny_position	*pos,
				      const t_bunny_size	*siz,
				      unsigned int		color,
				      t_transform		*t)
{
  unsigned int		col[2] = {color, color};
  t_bunny_position	cpos = {pos->x, pos->y};
  int			i;

  for (i = 0; str[i]; ++i)
    {
      int		c;

      if (str[i] >= 'A' && str[i] <= 'Z')
	c = str[i] - 'A' + BFT_A;
      else if (str[i] >= 'a' && str[i] <= 'z')
	c = str[i] - 'a' + BFT_A;
      else if (str[i] >= '0' && str[i] <= '9')
	c = str[i] - '0' + BFT_0;
      else if (str[i] == '!')
	c = BFT_EXCLAMATION;
      else
	c = -1;

      if (c >= 0)
	{
	  const t_bunny_letter *l = &gl_vector_font[c];
	  int		j;

	  for (j = 0; j < l->nb_edge; ++j)
	    {
	      t_bunny_position lpos[2] =
		{
		 [0] = {
			l->edge[j].x0 * siz->x / 20 + cpos.x,
			l->edge[j].y0 * siz->y / 20 + cpos.y
		 },
		 [1] = {
			l->edge[j].x1 * siz->x / 20 + cpos.x,
			l->edge[j].y1 * siz->y / 20 + cpos.y
		 },
		};

	      if (t == NULL)
		bunny_set_line(&win->buffer, &lpos[0], col);
	      else
		transform(win, lpos, col, t);
	    }
	}
      cpos.x += siz->x * 1.1;
    }
}
