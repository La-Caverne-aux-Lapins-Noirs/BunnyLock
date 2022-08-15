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

static void		transform_coords(t_bunny_position	*pos,
					 t_transform		*t)
{
  double		rotx, roty, rotz;
  double		x, y, z;
  double		xx, yy, zz;

  rotx = M_PI * t->rotx / 180.0;
  roty = M_PI * t->roty / 180.0;
  rotz = M_PI * t->rotz / 180.0;
  
  x = pos->x * t->xscale - t->center.x;
  y = pos->y * t->yscale - t->center.y;
  z = t->shiftz;

  xx = x * 1 + y * 0 + z * 0;
  yy = x * 0 + y * cos(rotx) - z * sin(rotx);
  zz = x * 0 + y * sin(rotx) + z * cos(rotx);

  x = xx * cos(roty) + yy * 0 + zz * sin(roty);
  y = xx * 0 + yy * 1 - zz * 0;
  z = -xx * sin(roty) + yy * 0 + zz * cos(roty);

  xx = x * cos(rotz) - y * sin(rotz) + z * 0;
  yy = x * sin(rotz) + y * cos(rotz) - z * 0;
  zz = x * 0 + y * 0 + z * 1;

  pos->x = xx + t->center.x;
  pos->y = yy + t->center.y;
}

void			transform(t_bunny_window		*win,
				  const t_bunny_position	*pos,
				  unsigned int			*color,
				  t_transform			*t)
{
  t_bunny_position	final[2];

  final[0] = pos[0];
  final[1] = pos[1];
  transform_coords(&final[0], t);
  transform_coords(&final[1], t);
  
  bunny_set_line(&win->buffer, final, color);
}
