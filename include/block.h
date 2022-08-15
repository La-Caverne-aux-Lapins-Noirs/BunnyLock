/*
** *****************************************************************************
** Jason Brillante "Damdoshi" <jason.brillante@gmail.com>
** Hanged Bunny Studio 2014-2019
**
** - Bunny Lock -
**
** *****************************************************************************
*/

#ifndef			__BUNNY_LOCK_H__
# define		__BUNNY_LOCK_H__
# include		<lapin.h>
# include		"block_api.h"

typedef struct		s_transform
{
  t_bunny_position	center;
  double		shiftz;
  double		rotx;
  double		roty;
  double		rotz;
  double		xscale;
  double		yscale;
}			t_transform;

typedef struct		s_bunny_stars
{
  size_t		length;
  t_bunny_vertex	vertex[1024];
  t_bunny_accurate_position pos[1024];
  t_bunny_accurate_position speed[1024];
  t_bunny_color		color[1024];
  int			radius;
}			t_bunny_stars;

typedef struct		s_bunny_builtin
{
  t_transform		transform;
  t_bunny_stars		stars;
}			t_bunny_builtin;

typedef struct		s_bunny_lock
{
  t_bunny_window	*win[16];
  size_t		nbr_win;
  void			*custom_data;

  void			*dynlib;
  t_bunny_display	custom_display;
  double		start_time;
  t_transform		clock_transform;
  int			last_rotation;
}			t_bunny_lock;

void			transform(t_bunny_window			*win,
				  const t_bunny_position		*pos,
				  unsigned int				*color,
				  t_transform				*t);

void			write_letters(t_bunny_window			*win,
				      const char			*str,
				      const t_bunny_position		*pos,
				      const t_bunny_size		*siz,
				      unsigned int			color,
				      t_transform			*transform);

t_bunny_response	bunny_lock_builtin_display(t_bunny_lock_shared_data		*lock);

#endif	/*		__BUNNY_LOCK_H__				*/
