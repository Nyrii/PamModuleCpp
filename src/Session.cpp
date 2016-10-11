/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Tue Oct 11 15:01:49 2016 wilmot_g
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
  if (_username == "root")
    return (Logger::get() << Logger::CRITICAL << "Root is not supported" << Logger::endl(), -1);
  return (0);
}

int   Session::open() {return (_container.open(_username));}
int   Session::close() {return (_container.close(_username));}
