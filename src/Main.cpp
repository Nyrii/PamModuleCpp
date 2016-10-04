/*
** Main.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 14:08:06 2016 wilmot_g
** Last update Tue Oct 04 14:12:08 2016 wilmot_g
*/

#include <security/pam_appl.h>
// #include <security/pam_misc.h>
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include "Session.hh"
#include "Errors.hh"

int			main(int ac, char **av) {
  pam_handle_t    *pamh;
  pam_conv		    conv;
  struct passwd   *passwd;
  int			        ret;

  (void)ac;
  (void)av;
  if (!(passwd = getpwuid(getuid())) || !passwd->pw_name)
    return (cerr << ERR_LOGIN << endl, -1);
  if ((ret = pam_start("vault", passwd->pw_name, &conv, &pamh)) == -1 || (ret = pam_authenticate(pamh, 0)) == -1 || (ret = pam_acct_mgmt(pamh, 0)) == -1)
    return (cerr << pam_strerror(pamh, ret) << endl, pam_end(pamh, ret), -1);
  pam_end(pamh, ret);
  return (0);
}
