//
// AESCrypt.hpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:27:08 2016 Nyrandone Noboud-Inpeng
// Last update Mon Oct 17 14:44:03 2016 Nyrandone Noboud-Inpeng
//

#ifndef AESCRYPT_HPP_
# define AESCRYPT_HPP_

# include <crypto++/aes.h>
# include <crypto++/osrng.h>
# include <iostream>
# include "Pamela.hh"
# include "Crypt.hpp"

# define  AES_KEYLEN  32
# define  DL_BYTES    100000
# define  KEY_FILE    ".aeskey"
# define  IV_FILE     ".aesIV"
# define  SIZE_FILE   ".containerSize"
# define  ROOT_PATH   "/root/cntr/"

using namespace CryptoPP;
using namespace std;

class AESCrypt : Crypt {

  public:
    AESCrypt() {

    };
    ~AESCrypt() {};

    int                   init(const string &);
    int                   encrypt(const string &, const string &);
    int                   decrypt(const string &, const string &);
    int                   readKeys(const string &);
    int                   getFilePreviousSize(const string &);

    AutoSeededRandomPool  _randomGenerator;
    SecByteBlock          _aesKey, _aesIV;
};

#endif /* !AESCRYPT_HPP_ */
