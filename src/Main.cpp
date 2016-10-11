/*
** Main.cpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 14:08:06 2016 wilmot_g
** Last update Tue Oct 11 18:04:34 2016 Nyrandone Noboud-Inpeng
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
  struct stat buf;

  stat(av[1], &buf);
  crypt.init();
  crypt.encrypt(av[1]);
  crypt.decrypt("crypt.txt", buf.st_size);



  // AutoSeededRandomPool  rnd;
  //
  // // Generate a random key
  // SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
  // rnd.GenerateBlock( key, key.size() );
  //
  // // Generate a random IV
  // unsigned char iv[AES::BLOCKSIZE];
  // rnd.GenerateBlock(iv, AES::BLOCKSIZE);
  //
  // int size;
  // std::ifstream ifs;
  //
  // ifs.open(av[1], std::ifstream::in | std::ifstream::ate | std::ifstream::binary);
  // ifs.seekg(0, ifs.end);
  // size = ifs.tellg();
  // ifs.close();
  //
  // unsigned char *buffer = new unsigned char[size + 1];
  // memset(buffer, 0, size + 1);
  //
  // ifs.open(av[1], std::ios::binary | std::ios::in | std::ios::ate);
  // ifs.seekg(0, std::ios::beg);
  // if (ifs.read(reinterpret_cast<char *>(buffer), size)) {
  //
  //   //////////////////////////////////////////////////////////////////////////
  //   // Encrypt
  //   try {
  //     CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
  //     cfbEncryption.ProcessData(buffer, buffer, size);
  //     std::ofstream myfile;
  //     myfile.open("crypt.txt");
  //     myfile << buffer;
  //     myfile.close();
  //   } catch (CryptoPP::Exception &e) {
  //     std::cerr << e.what() << std::endl;
  //     return (-1);
  //   }
  // }
  // ifs.close();
  // //////////////////////////////////////////////////////////////////////////
  // // Decrypt
  //
  // // Add new and/or malloc : error wtf
  //
  // int previousSize = size;
  // ifs.open("crypt.txt", std::ios::in | std::ios::ate | std::ios::binary);
  // ifs.seekg(0, std::ios::beg);
  //
  // struct stat buf;
  // if (stat("crypt.txt", &buf) == -1) {
  //   std::cerr << "putain" << std::endl;
  // } else {
  //   std::cout << "size = " << buf.st_size << std::endl;
  // }
  // if (ifs.read(reinterpret_cast<char *>(buffer), buf.st_size)) {
  //   CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
  //   cfbDecryption.ProcessData(buffer, buffer, previousSize);
  //   std::cout << buffer << std::endl;
  // } else {
  //   std::cerr << "Sale merde" << std::endl;
  // }
  // return (0);
}
