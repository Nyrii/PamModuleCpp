//
// AESCrypt.hpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:27:08 2016 Nyrandone Noboud-Inpeng
// Last update Wed Oct 12 14:27:28 2016 Nyrandone Noboud-Inpeng
//

#ifndef AESCRYPT_HPP_
# define AESCRYPT_HPP_

# include <crypto++/aes.h>
# include <crypto++/osrng.h>
# include <crypto++/blowfish.h>
# include <iostream>
# include "Pamela.hh"
# include "Crypt.hpp"

# define  AES_KEYLEN  32
# define  DL_BYTES    100000

using namespace CryptoPP;
using namespace std;

class AESCrypt : Crypt {

  public:
    AESCrypt() {

    };
    ~AESCrypt() {};

    int                   init();
    int                   encrypt(const string &file);
    int                   decrypt(const string &file, const string &, int const);

    AutoSeededRandomPool  _randomGenerator;
    SecByteBlock          _aesKey, _aesIV;
};

#endif /* !AESCRYPT_HPP_ */
