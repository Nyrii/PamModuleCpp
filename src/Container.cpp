//
// Container.cpp for Container in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 14:59:30 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct  4 15:44:40 2016 Nyrandone Noboud-Inpeng
//

#include "Container.hpp"
#include "Errors.hpp"

int Container::init()
{
  _rsaEncryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];
  _aesEncryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];

  _rsaDecryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];
  _aesDecryptCtx = new EVP_CIPHER_CTX[sizeof(EVP_CIPHER_CTX)];

  if (_rsaEncryptCtx == NULL || _aesEncryptCtx == NULL
      || _rsaDecryptCtx == NULL || _aesDecryptCtx == NULL) {
    throw MemoryAllocError("Error : memory allocation failed.");
  }
  return (0);
}

int Container::openContainer()
{
  return (0);
}

int Container::closeContainer()
{
  return (0);
}

int Container::encrypt()
{
  return (0);
}

int Container::decrypt()
{
  return (0);
}
