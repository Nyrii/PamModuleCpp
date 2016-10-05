/*
** pamela.cpp for Shared in /home/wilmot_g/Epitech/Crypto/Shared
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 03 21:19:49 2016 wilmot_g
** Last update Wed Oct 05 19:42:43 2016 wilmot_g
*/

#include <iostream>
#include "Pamela.hh"
#include "Session.hh"
#include "Logger.hpp"

#define			PAM_SM_SESSION

void              checkArgs(int ac, const char **av, int flags) {
  if (ac < 1)
    return;
  for (int i = 0; i < ac; i++)
    if (string(av[i]) == "silent")
      Logger::get().silence(true);

  Logger::get() << Logger::DEBUG << "Flags : " << flags << Logger::endl();
  Logger::get() << Logger::DEBUG << "Arg count : " << ac << Logger::endl();
  for (int i = 0; i < ac; i++)
    Logger::get() << "av[" << i << "] = " << av[i] << Logger::endl();
}

PAM_EXTERN int		pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  checkArgs(ac, av, flags);
  Logger::get() << Logger::DEBUG << "Open Session" << Logger::endl();
  if (!pamh)
    return (Logger::get() << Logger::CRITICAL << "Pam handle is NULL" << Logger::endl(), PAM_SESSION_ERR);

  Session session;
  if (session.init(pamh) == -1)
    return (PAM_SESSION_ERR);
  return (PAM_SUCCESS);
}

PAM_EXTERN int		pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  checkArgs(ac, av, flags);
  Logger::get() << Logger::DEBUG << "Close Session" << Logger::endl();
  if (!pamh)
    return (Logger::get() << Logger::CRITICAL << "Pam handle is NULL" << Logger::endl(), PAM_SESSION_ERR);

  (void)pamh;
  (void)flags;
  (void)ac;
  (void)av;
  return (PAM_SUCCESS);
}
