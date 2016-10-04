//
// Container.hpp for Container in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 13:33:28 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct  4 15:20:15 2016 Nyrandone Noboud-Inpeng
//

#ifndef CONTAINER_HPP_
# define CONTAINER_HPP_

# include <openssl/sha.h>
# include <openssl/evp.h>

class Container {

  public:
    Container() {
      localKeypair = NULL;
      remotePubKey = NULL;

      rsaEncryptCtx = NULL;
      aesEncryptCtx = NULL;

      rsaDecryptCtx = NULL;
      aesDecryptCtx = NULL;

      aesKey = NULL;
      aesIV = NULL;
    }

    ~Container() {}

    int init();
    int openContainer();
    int closeContainer();
    int encrypt();
    int decrypt();

  private:
    static EVP_PKEY *localKeypair;
    EVP_PKEY        *remotePubKey;

    EVP_CIPHER_CTX  *rsaEncryptCtx;
    EVP_CIPHER_CTX  *aesEncryptCtx;

    EVP_CIPHER_CTX  *rsaDecryptCtx;
    EVP_CIPHER_CTX  *aesDecryptCtx;

    unsigned char   *aesKey;
    unsigned char   *aesIV;
};

#endif /* !CONTAINER_HPP_ */
