/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Tue Oct 04 14:02:02 2016 wilmot_g
*/

#include <iostream>
#include "Session.hh"

Session::Session() {}
Session::~Session() {}

int   Session::init(pam_handle_t *pamh, int flags, int ac, const char **av) {
  (void)pamh;
  _silent = (flags == PAM_SILENT) ? true : false;
  cout << flags << endl;
  cout << ac << endl;
  for (int i = 0; i < ac - 1; i++)
    cout << av[i] << endl;
  return (0);
}
