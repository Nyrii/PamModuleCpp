/*
** Session.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:40:45 2016 wilmot_g
** Last update Wed Oct 05 16:13:28 2016 wilmot_g
*/

#include <iostream>
#include "Session.hh"

Session::Session() {}
Session::~Session() {}

int   Session::init(pam_handle_t *pamh, int flags, int ac, const char **av) {
  if (!pamh)
    return (cerr << "Pam handle is NULL" << endl, -1);
  _silent = (flags == PAM_SILENT) ? true : false;

  //Debug
  cout << "Flags : " << flags << endl;
  cout << "Arg count : " << ac << endl;
  for (int i = 0; i < ac - 1; i++)
    cerr << "av[" << i << "] = " << av[i] << endl;

  return (0);
}
