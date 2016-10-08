//
// Crypt.hpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Oct  8 15:48:30 2016 Nyrandone Noboud-Inpeng
// Last update Sat Oct  8 15:48:51 2016 Nyrandone Noboud-Inpeng
//

#ifndef CRYPT_HPP_
# define CRYPT_HPP_

# include <openssl/sha.h>
# include <openssl/evp.h>
# include <openssl/rsa.h>

# define RSA_KEYLEN 2048

class Crypt {

  public:
    Crypt() {
      _localKeypair = NULL;
      _remotePubKey = NULL;

      _rsaEncryptCtx = NULL;
      _aesEncryptCtx = NULL;

      _rsaDecryptCtx = NULL;
      _aesDecryptCtx = NULL;

      _aesKey = NULL;
      _aesIV = NULL;
    };

    ~Crypt() {};

    int init();
    int encrypt();
    int decrypt();

  private:
    EVP_PKEY        *_localKeypair;
    EVP_PKEY        *_remotePubKey;

    EVP_CIPHER_CTX  *_rsaEncryptCtx;
    EVP_CIPHER_CTX  *_aesEncryptCtx;

    EVP_CIPHER_CTX  *_rsaDecryptCtx;
    EVP_CIPHER_CTX  *_aesDecryptCtx;

    unsigned char   *_aesKey;
    unsigned char   *_aesIV;
};

#endif /* !CRYPT_HPP_ */
