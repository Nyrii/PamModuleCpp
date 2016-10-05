/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Wed Oct 05 19:43:05 2016 wilmot_g
*/

#include <iostream>
#include "Logger.hpp"
#include "Session.hh"

Session::Session() {}
Session::~Session() {}

int   Session::init(pam_handle_t *pamh) {
  const char    *username;
  if (pam_get_user(pamh, &username, NULL) == -1)
    return (Logger::get() << Logger::CRITICAL << "Can't get username" << Logger::endl(), -1);
  _username = username;
  Logger::get() << Logger::DEBUG << "Username : [" << _username << "]" << Logger::endl();
  return (0);
}
