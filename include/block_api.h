/*
** *****************************************************************************
** Jason Brillante "Damdoshi" <jason.brillante@gmail.com>
** Hanged Bunny Studio 2014-2019
**
** - Bunny Lock -
**
** *****************************************************************************
*/

#ifndef			__BUNNY_LOCK_API_H__
# define		__BUNNY_LOCK_API_H__

typedef struct		s_bunny_lock_shared_data
{
  t_bunny_window	*win[16];
  size_t		nbr_win;
  void			*custom_data;
}			t_bunny_lock_shared_data;

#endif	/*		__BUNNY_LOCK_API_H__		*/

