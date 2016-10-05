//
// Container.hpp for Container in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 13:33:28 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct  4 16:30:04 2016 Nyrandone Noboud-Inpeng
//

#ifndef CONTAINER_HPP_
# define CONTAINER_HPP_

# include <openssl/sha.h>
# include <openssl/evp.h>

class Container {

  public:
    Container() {
      _localKeypair = NULL;
      _remotePubKey = NULL;

      _rsaEncryptCtx = NULL;
      _aesEncryptCtx = NULL;

      _rsaDecryptCtx = NULL;
      _aesDecryptCtx = NULL;

      _aesKey = NULL;
      _aesIV = NULL;
    };

    ~Container() {};

    int init();
    int openContainer();
    int closeContainer();
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

#endif /* !CONTAINER_HPP_ */
