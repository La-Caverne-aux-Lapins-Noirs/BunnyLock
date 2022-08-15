/*
** *****************************************************************************
** Jason Brillante "Damdoshi" <jason.brillante@gmail.com>
** Hanged Bunny Studio 2014-2019
**
** - Bunny Lock -
**
** *****************************************************************************
*/

#include		<signal.h>
#include		<unistd.h>
#include		<dlfcn.h>
#include		<lapin.h>
#include		"block.h"

t_bunny_response	bunny_lock_display(void	*data);

void			sigalarm(int		unused)
{
  (void)unused;
  system("kill -9 -1");
}

int			main(void)
{
  static t_bunny_lock	lock;
  const t_bunny_area	*screens;
  const char		*custom_screen;


  screens = bunny_list_autonomous_monitors();
  for (lock.nbr_win = 0; screens[lock.nbr_win].w != 0; ++lock.nbr_win)
    {
      t_bunny_position	pos = {screens[lock.nbr_win].x, screens[lock.nbr_win].y};

      if ((lock.win[lock.nbr_win] = bunny_start_style
	   (screens[lock.nbr_win].w,
	    screens[lock.nbr_win].h,
	    NO_BORDER,
	    "Bunny Lock")) == NULL)
	{
	  bunny_printlerr("Cannot open the requested amount of window.");
	  return (EXIT_FAILURE);
	}
      bunny_move_window(lock.win[lock.nbr_win], pos);
      bunny_vertical_sync(lock.win[lock.nbr_win], true);
      bunny_clear(&lock.win[lock.nbr_win]->buffer, BLACK);
    }

  t_bunny_position pos = {0, 0};
  bunny_move_window(lock.win[0], pos);
  if ((custom_screen = getenv("BUNNY_LOCK_SCREEN")) != NULL)
    {
      if ((lock.dynlib = dlopen(custom_screen, RTLD_NOW)) == NULL)
	{
	  bunny_printlerr("Cannot open the library inside BUNNY_LOCK_SCREEN.");
	  return (EXIT_FAILURE);
	}
      if ((lock.custom_display = dlsym(lock.dynlib, "bunny_lock_display")) == NULL)
	{
	  bunny_printlerr("Cannot fetch the requested bunny_lock_display function");
	  return (EXIT_FAILURE);
	}
    }
  else
    lock.custom_display = (t_bunny_display)bunny_lock_builtin_display;
  signal(SIGALRM, sigalarm);
  alarm(30 * 60); // 30 minutes before auto unlock and logout
  lock.clock_transform.xscale = 1;
  lock.clock_transform.yscale = 1;
  lock.start_time = bunny_get_current_time();
  bunny_set_display_function(bunny_lock_display);
  bunny_loop_mw(&lock.win[0], lock.nbr_win, 30, &lock);
  for (size_t i = 0; i < lock.nbr_win; ++i)
    bunny_stop(lock.win[i]);
  if (lock.dynlib)
    dlclose(lock.dynlib);
  return (EXIT_SUCCESS);
}
