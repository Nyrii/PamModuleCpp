/*
** Main.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 14:08:06 2016 wilmot_g
** Last update Wed Oct 12 18:42:43 2016 Nyrandone Noboud-Inpeng
*/

#include <security/pam_appl.h>
// #include <security/pam_misc.h>
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include "Session.hh"
#include "Pamela.hh"
#include "Errors.hpp"

int     log() {
  pam_handle_t    *pamh;
  pam_conv		    conv;
  struct passwd   *passwd;
  int			        ret;

  if (!(passwd = getpwuid(getuid())) || !passwd->pw_name)
    return (cerr << ERR_LOGIN << endl, -1);
  if ((ret = pam_start("vault", passwd->pw_name, &conv, &pamh)) == -1 || (ret = pam_authenticate(pamh, 0)) == -1 || (ret = pam_acct_mgmt(pamh, 0)) == -1)
    return (cerr << pam_strerror(pamh, ret) << endl, pam_end(pamh, ret), -1);
  pam_end(pamh, ret);
  return (0);
}

#include <crypto++/aes.h>
#include <crypto++/filters.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <fstream>
#include <sys/stat.h>
#include "AESCrypt.hpp"

using namespace CryptoPP;

int			main(UNUSED int ac, UNUSED char **av) {

  // log();

  // Encryption / Decryption
  // Crypt crypter;

  AESCrypt crypt;

  crypt.init();
  crypt.encrypt(av[1]);
  // crypt.readKeys();
  crypt.decrypt("crypt.txt", "panda.jpg");
  return (0);
}
