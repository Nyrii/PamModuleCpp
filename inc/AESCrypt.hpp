//
// AESCrypt.hpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:27:08 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct 11 16:40:20 2016 Nyrandone Noboud-Inpeng
//

#ifndef AESCRYPT_HPP_
# define AESCRYPT_HPP_

# include <crypto++/aes.h>
# include <crypto++/osrng.h>
# include <iostream>
# include "Pamela.hh"
# include "Crypt.hpp"

using namespace CryptoPP;
using namespace std;

class AESCrypt : Crypt {

  public:
    AESCrypt() : _aesKey(0x00, AES::DEFAULT_KEYLENGTH) {

    };
    ~AESCrypt() {};

    int                   init();
    int                   encrypt(const string &file);
    int                   decrypt(const string &file, int const);

    AutoSeededRandomPool  _randomGenerator;
    SecByteBlock          _aesKey;
    unsigned char         _aesIV[AES::BLOCKSIZE];
};

#endif /* !AESCRYPT_HPP_ */
