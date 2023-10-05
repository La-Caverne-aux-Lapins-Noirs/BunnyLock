/*
** *****************************************************************************
** Jason Brillante "Damdoshi" <jason.brillante@gmail.com>
** Hanged Bunny Studio 2014-2019
**
** - Bunny Lock -
**
** *****************************************************************************
*/

#include		<math.h>
#include		"block.h"

size_t			count_line(const char				*str)
{
  size_t		i;
  size_t		cnt = 0;

  for (i = 0; str[i]; ++i)
    if (str[i] == '\n')
      cnt += 1;
  return (cnt + 1);
}

static bool		try_init(t_bunny_lock_shared_data		*lck)
{
  if (lck->custom_data)
    return (true);
  if ((lck->custom_data = calloc(1, sizeof(t_bunny_builtin))) == NULL)
    return (false);
  t_bunny_builtin	*bu = lck->custom_data;

  bu->transform.xscale = 1;
  bu->transform.yscale = 1;

  bu->stars.radius = 0;
  bu->stars.length = NBRCELL(bu->stars.vertex);
  for (size_t i = 0; i < lck->nbr_win; ++i)
    {
      if (bu->stars.radius < lck->win[i]->buffer.width / 2)
	bu->stars.radius = lck->win[i]->buffer.width / 2;
      if (bu->stars.radius < lck->win[i]->buffer.height / 2)
	bu->stars.radius = lck->win[i]->buffer.height / 2;
    }
  for (size_t i = 0; i < bu->stars.length; ++i)
    {
      double		angle = (rand() % (int)(2 * 1e6 * M_PI)) / 1e6;
      double		init_pos = rand() % (bu->stars.radius + 1);
      double		init_speed = rand() % 20;

      bu->stars.speed[i].x = cos(angle) * init_speed;
      bu->stars.speed[i].y = sin(angle) * init_speed;
      bu->stars.pos[i].x = cos(angle) * init_pos;
      bu->stars.pos[i].y = sin(angle) * init_pos;
      bu->stars.color[i].full = ALPHA(0, WHITE);
    }
  return (true);
}

static t_bunny_response	lock_builtin_display(t_bunny_lock_shared_data	*lcks,
					     t_bunny_window		*win)
{
  t_bunny_builtin	*lck = lcks->custom_data;

  // Place stars on screen
  for (size_t i = 0; i < lck->stars.length; ++i)
    {
      lck->stars.vertex[i].pos.x =
	lck->stars.pos[i].x + win->buffer.width / 2;
      lck->stars.vertex[i].pos.y =
	lck->stars.pos[i].y + win->buffer.height / 2;
      lck->stars.vertex[i].color = lck->stars.color[i].full;
    }
  bunny_set_geometry(&win->buffer, BGY_PIXELS, (t_bunny_vertex_array*)&lck->stars.length, NULL);

  /// LETTRES 3D

  const char		*str = "E F R\nI T S";
  t_bunny_position	pos;
  t_bunny_size		siz;

  siz.x = win->buffer.width / (2 * strlen(str));
  siz.y = win->buffer.height / (2 * count_line(str));
  if (siz.x > siz.y)
    siz.x = siz.y;
  else
    siz.y = siz.x;
  pos.x = (win->buffer.width - strlen(str) * siz.x) / 2;
  pos.y = (win->buffer.height - siz.y) / 2;

  lck->transform.rotx += 3;
  lck->transform.roty += 2;
  double		tim = bunny_get_current_time();

  lck->transform.rotz = cos(tim) * 40;

  lck->transform.center.x = win->buffer.width / 2;
  lck->transform.center.y = win->buffer.height / 2;

  lck->transform.shiftz = cos(tim) * 10;

  for (int i = 0; i < 5; ++i)
    {
      write_letters
	(win, str, &pos, &siz,
	 YELLOW | GRAY(128), &lck->transform
	 );
      pos.x += 1;
      pos.y += 1;
    }

  pos.x -= 2;
  pos.y -= 2;
  for (int j = 0; j < 3; ++j)
    {
      lck->transform.shiftz = -cos(tim) * 10 * (j + 1);
      write_letters
	(win, str, &pos, &siz,
	 RED | GRAY(128), &lck->transform
	 );
    }

  bunny_fill(&win->buffer, ALPHA(64, BLACK));
  return (GO_ON);
}

t_bunny_response	bunny_lock_builtin_display(t_bunny_lock_shared_data	*lck)
{
  t_bunny_response	ret;

  if (try_init(lck) == false)
    return (GO_ON);
  t_bunny_builtin	*cd = lck->custom_data;

  /// STARFIELD
  // Move stars
  for (size_t i = 0; i < cd->stars.length; ++i)
    {
      cd->stars.pos[i].x += cd->stars.speed[i].x;
      cd->stars.pos[i].y += cd->stars.speed[i].y;
      if (cd->stars.color[i].argb[ALPHA_CMP] < 250)
	cd->stars.color[i].argb[ALPHA_CMP] += 5;
      if (fabs(cd->stars.pos[i].x) > cd->stars.radius ||
	  fabs(cd->stars.pos[i].y) > cd->stars.radius)
	{
	  double		angle = (rand() % (int)(2 * 1e6 * M_PI)) / 1e6;
	  double		init_speed = rand() % 17 + 3;

	  cd->stars.speed[i].x = cos(angle) * init_speed;
	  cd->stars.speed[i].y = sin(angle) * init_speed;
	  cd->stars.pos[i].x = cos(angle) * cd->stars.radius * 0.2;
	  cd->stars.pos[i].y = sin(angle) * cd->stars.radius * 0.2;
	  cd->stars.color[i].full = ALPHA(0, WHITE);
	}
    }

  for (size_t i = 0; i < lck->nbr_win; ++i)
    if ((ret = lock_builtin_display(lck, lck->win[i])) != GO_ON)
      return (ret);
  return (GO_ON);
}
