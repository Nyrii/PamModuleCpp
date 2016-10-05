/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Wed Oct 05 18:02:00 2016 wilmot_g
*/

#include <iostream>
#include "Logger.hpp"
#include "Session.hh"

Session::Session() {}
Session::~Session() {}

int   Session::init(pam_handle_t *pamh, int flags, int ac, const char **av) {
  if (flags == PAM_SILENT)
    Logger::get().silence(true);
  if (!pamh)
    return (Logger::get() << Logger::CRITICAL << "Pam handle is NULL" << Logger::endl(), -1);

  //Debug
  Logger::get() << Logger::DEBUG << "Flags : " << flags << Logger::endl();
  Logger::get() << Logger::DEBUG << "Arg count : " << ac << Logger::endl();
  for (int i = 0; i < ac - 1; i++)
    Logger::get() << "av[" << i << "] = " << av[i] << Logger::endl();

  return (0);
}
