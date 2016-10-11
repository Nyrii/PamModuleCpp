/*
** Logger.cpp for  in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 05 16:19:57 2016 wilmot_g
** Last update Tue Oct 11 13:56:43 2016 wilmot_g
*/

#include "Logger.hpp"

Logger::Logger() {
  _silent = false;
  _prefix[Logger::DEBUG] = string("[") + "\033[01;35m" + "DEBUG" + "\033[0m" + "] ";
  _prefix[Logger::WARN] = string("[") + "\033[01;33m" + "WARN" + "\033[0m" + "] ";
  _prefix[Logger::CRITICAL] = string("[") + "\033[01;31m" + "CRITICAL" + "\033[0m" + "] ";
  _prefix[Logger::SUCCESS] = string("[") + "\033[01;32m" + "SUCCESS" + "\033[0m" + "] ";
}

void        Logger::prioritize(Logger::Priority p) {*this << (_prefix[p]);}
void        Logger::silence(bool s) {_silent = s;}
