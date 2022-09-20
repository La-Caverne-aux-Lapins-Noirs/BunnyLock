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

t_bunny_response	bunny_lock_display(t_bunny_lock		*lck)
{
  int			remaining = (30 * 60) - (bunny_get_current_time() - lck->start_time);
  // int			remaining = bunny_get_current_time() - lck->start_time;
  char			buffer[32];
  t_bunny_response	ret;
  size_t		i;

  if (lck->custom_display)
    if ((ret = lck->custom_display
	 ((t_bunny_lock_shared_data*)lck)) != GO_ON)
      return (ret);

  ////////////////////////////
  // Display remaining time //
  ////////////////////////////

  // if (remaining < 0)
  if (remaining < 0)
    {
      for (i = 0; i < lck->nbr_win; ++i)
	bunny_display(lck->win[i]);
      return (GO_ON);
    }
  t_bunny_position	pos;
  t_bunny_size		siz;
  t_transform		*t = &lck->clock_transform;

  siz.x = 50;
  siz.y = 50;

  snprintf(&buffer[0], sizeof(buffer), "%02d %02d", remaining / 60, remaining % 60);

  if (remaining % 60 == 0 && lck->last_rotation != remaining)
    {
      int		sel = rand() % 5;

      lck->last_rotation = remaining;
      t = &lck->clock_transform;

      if (sel == 0)
	t->rotx = 360;
      else if (sel == 1)
	t->roty = 360;
      else if (sel == 2)
	t->rotz = 360;
      else if (sel == 3)
	{
	  t->rotx = 180;
	  t->rotz = 180;
	}
      else if (sel == 4)
	{
	  t->roty = 180;
	  t->rotz = 180;
	}
      else if (sel == 5)
	{
	  t->rotx = 180;
	  t->roty = 180;
	}
    }

  for (i = 0; i < lck->nbr_win; ++i)
    {
      for (int j = 20; j >= 0; --j)
	{
	  int colratio = (int)(((double)j / 20) * 255);

	  pos.x = siz.x + 20 - j;
	  pos.y = lck->win[i]->buffer.height - siz.y * 2 + 20 - j;
	  if (t)
	    {
	      t->center.x = pos.x + (strlen(buffer) * siz.x) / 2;
	      t->center.y = pos.y + siz.y / 2;
	    }
	  write_letters
	    (lck->win[i], &buffer[0], &pos, &siz,
	     ALPHA(colratio, WHITE), t);
	}
      bunny_display(lck->win[i]);
    }

  bunny_reach(&lck->clock_transform.rotx, 0, 5);
  bunny_reach(&lck->clock_transform.roty, 0, 5);
  bunny_reach(&lck->clock_transform.rotz, 0, 5);
  return (GO_ON);
}
