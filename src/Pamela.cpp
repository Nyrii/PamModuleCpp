/*
** pamela.cpp for Shared in /home/wilmot_g/Epitech/Crypto/Shared
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 03 21:19:49 2016 wilmot_g
** Last update Tue Oct 04 14:13:54 2016 wilmot_g
*/

#include <iostream>
#include "Session.hh"

#define			PAM_SM_AUTH
#define			PAM_SM_SESSION

extern int		pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  Session session;

  cout << "Open Session" << endl;

  if (!pamh)
    return (PAM_SESSION_ERR);
  if (session.init(pamh, flags, ac, av) == -1)
    return (PAM_SESSION_ERR);
  return (PAM_SUCCESS);
}

extern int		pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{

  cout << "Close Session" << endl;

  (void)pamh;
  (void)flags;
  (void)ac;
  (void)av;
  return (0);
}
