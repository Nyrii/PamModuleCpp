//
// Crypt.cpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Oct  8 15:49:06 2016 Nyrandone Noboud-Inpeng
// Last update Sat Oct  8 21:55:17 2016 Nyrandone Noboud-Inpeng
//

# include <openssl/rsa.h>
# include <openssl/rand.h>
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

  try {
    generateRSAKey();
    generateAESKeyAndIV();
  } catch (Error &e){
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}

int Crypt::generateRSAKey()
{
  // Generate a 2048 bit RSA key
  // Allocates public key algorithm context using the algorithm specified by id.
  EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

  if (ctx == NULL
      || EVP_PKEY_keygen_init(ctx) <= 0 /* Generate key */
      || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEYLEN) <= 0 /* Initialize key length */
      || EVP_PKEY_keygen(ctx, &_localKeypair) <= 0) /* Generated key is written into localKeyPair */ {
    throw CryptError("Error : RSA init failed.");
  }
  EVP_PKEY_CTX_free(ctx);
  return (0);
}

int Crypt::generateAESKeyAndIV()
{
  if (!(_aesKey = new unsigned char[AES_KEYLEN / 8])
      || !(_aesIV = new unsigned char[AES_KEYLEN / 8])
      || !(_aesPass = new unsigned char[AES_KEYLEN / 8])
      || !(_aesSalt = new unsigned char[8])) {
    throw MemoryAllocError("Error : memory allocation failed.");
  }
  if (RAND_bytes(_aesPass, AES_KEYLEN / 8) <= 0 || RAND_bytes(_aesSalt, 8) <= 0) {
    throw CryptError("Error : crypt error on putting pseudo-random bytes into buffers.");
  }
  if (EVP_BytesToKey(EVP_aes_128_cbc(), EVP_sha256(), _aesSalt, _aesPass, AES_KEYLEN / 8, AES_ROUNDS, _aesKey, _aesIV) == 0) {
    throw CryptError("Error : could not generate derivated AES key or AES IV.");
  }
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
