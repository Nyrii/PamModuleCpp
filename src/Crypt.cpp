//
// Crypt.cpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Oct  8 15:49:06 2016 Nyrandone Noboud-Inpeng
// Last update Sat Oct  8 15:54:14 2016 Nyrandone Noboud-Inpeng
//

#include "Crypt.hpp"
#include "Errors.hpp"

int Crypt::init()
{
  _rsaEncryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];
  _aesEncryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];

  _rsaDecryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];
  _aesDecryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];

  if (_rsaEncryptCtx == NULL || _aesEncryptCtx == NULL
      || _rsaDecryptCtx == NULL || _aesDecryptCtx == NULL) {
    throw MemoryAllocError("Error : memory allocation failed.");
  }

  // Clears all informations from a cipher context and free up any allocated memory associate with it, except the ctx itself.
  EVP_CIPHER_CTX_init(_rsaEncryptCtx);
  EVP_CIPHER_CTX_init(_aesEncryptCtx);

  EVP_CIPHER_CTX_init(_rsaDecryptCtx);
  EVP_CIPHER_CTX_init(_aesDecryptCtx);

  // Generate a 2048 bit RSA key
    // Allocates public key algorithm context using the algorithm specified by id.
  EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
  EVP_PKEY *privateKey = NULL;
  if (ctx == NULL
      || EVP_PKEY_keygen_init(ctx) <= 0
      || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEYLEN) <= 0
      || EVP_PKEY_keygen(ctx, &privateKey) <= 0) {
    throw CryptError("Error : RSA init failed.");
  }

  (void)ctx;

  return (0);
}

int Crypt::encrypt()
{
  return (0);
}

int Crypt::decrypt()
{
  return (0);
}
