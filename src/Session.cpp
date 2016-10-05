/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Wed Oct 05 18:28:25 2016 wilmot_g
*/

#include <iostream>
#include "Logger.hpp"
#include "Session.hh"

Session::Session() {}
Session::~Session() {}

int   Session::init(pam_handle_t *pamh) {
  if (!pamh)
    return (Logger::get() << Logger::CRITICAL << "Pam handle is NULL" << Logger::endl(), -1);
  return (0);
}
