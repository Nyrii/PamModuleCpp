/*
** pamela.cpp for Shared in /home/wilmot_g/Epitech/Crypto/Shared
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 03 21:19:49 2016 wilmot_g
** Last update Mon Oct  3 23:31:45 2016 Nyrandone Noboud-Inpeng
*/

#include <security/pam_appl.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
// #include <security/pam_misc.h>
#include "errors.hh"

using namespace std;

int   main(int ac, char **av) {
  pam_handle_t  *pam;
  pam_conv      conv;
  char          *login;
  int           ret;
  int           retval;

  if ((login = getlogin()) == NULL) return (cerr << ERR_LOGIN << endl, -1);
  if ((ret = pam_start("vault", login, &conv, &pam)) == -1 || (ret = pam_authenticate(pam, 0)) == -1 || (ret = pam_acct_mgmt(pam, 0)) == -1)
    return (cerr << pam_strerror(pam, retval) << endl, -1);
  cout << ret << endl;
  pam_end(pam, ret);
  return (0);
}
