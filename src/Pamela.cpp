/*
** pamela.cpp for Shared in /home/wilmot_g/Epitech/Crypto/Shared
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 03 21:19:49 2016 wilmot_g
** Last update Tue Oct  4 13:12:40 2016 Nyrandone Noboud-Inpeng
*/

#include <security/pam_appl.h>
// #include <security/pam_misc.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "Errors.hh"
#include "Pamela.hh"

using namespace std;

#define			PAM_SM_AUTH
#define			PAM_SM_SESSION

extern int		pam_sm_open_session(UNUSED pam_handle_t *pamh, UNUSED int flags,
                                  UNUSED int argc, UNUSED const char **argv)
{
  if (!pamh)
    return (PAM_SESSION_ERR);
  return (PAM_SUCCESS);
}

extern int		pam_sm_close_session(UNUSED pam_handle_t *pamh, UNUSED int flags,
                                    UNUSED int argc, UNUSED const char **argv)
{
  return (0);
}

int			main(UNUSED int ac, UNUSED char **av) {
  pam_handle_t		*pamh;
  pam_conv		conv;
  char			*login;
  int			ret;

  if (!(login = getlogin())) return (cerr << ERR_LOGIN << endl, -1);
  if ((ret = pam_start("vault", login, &conv, &pamh)) == -1 || (ret = pam_authenticate(pamh, 0)) == -1 || (ret = pam_acct_mgmt(pamh, 0)) == -1)
    return (cerr << pam_strerror(pamh, ret) << endl, pam_end(pamh, ret), -1);
  cout << ret << endl;
  pam_end(pamh, ret);
  return (0);
}
