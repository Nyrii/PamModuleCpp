//
// Crypt.cpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Oct  8 15:49:06 2016 Nyrandone Noboud-Inpeng
// Last update Sun Oct  9 16:18:18 2016 Nyrandone Noboud-Inpeng
//

#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <fstream>
#include <vector>
#include "Crypt.hpp"
#include "Errors.hpp"

int               Crypt::init()
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

int                 Crypt::generateRSAKey()
{
  // Generate a 2048 bit RSA key
  // Allocates public key algorithm context using the algorithm specified by id.
  EVP_PKEY_CTX  *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

  if (ctx == NULL
      || EVP_PKEY_keygen_init(ctx) <= 0 /* Generate key */
      || EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEYLEN) <= 0 /* Initialize key length */
      || EVP_PKEY_keygen(ctx, &_localKeypair) <= 0) /* Generated key is written into localKeyPair */ {
    throw CryptError("Error : RSA init failed.");
  }
  EVP_PKEY_CTX_free(ctx);
  return (0);
}

int                 Crypt::generateAESKeyAndIV()
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
  if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), _aesSalt, _aesPass, AES_KEYLEN / 8, AES_ITERATOR, _aesKey, _aesIV) == 0) {
    throw CryptError("Error : could not generate derivated AES key or AES IV.");
  }
  return (0);
}

int                 Crypt::getFileContentSize(std::string file) {
  std::ifstream     ifs;
  int               size;

  ifs.open(file.c_str(), std::ifstream::in | std::ifstream::ate | std::ifstream::binary);
  size = ifs.tellg();
  ifs.close();
  return (size);
}

int                 Crypt::RSAEncrypt()
{
  return (0);
}

int                 Crypt::RSADecrypt()
{
  return (0);
}

int                 Crypt::AESEncrypt(UNUSED std::string file)
{
  unsigned char     *fileEncryptedContent;
  int               bytesWritten = 0;
  int               bytesOfDataEncrypted = 0;
  int               fileContentSize = getFileContentSize(file);
  std::ifstream     ifs;
  std::vector<char> buffer(AES_BLOCK_SIZE + fileContentSize + 1);

  if (fileContentSize == -1) {
    return (std::cerr << "The file " << file << " is currently empty." << std::endl, 0);
  }
  if (!(fileEncryptedContent = new unsigned char[AES_BLOCK_SIZE + fileContentSize + 1])) {
    throw MemoryAllocError("Error : could not allocate memory.");
  }
  if (!EVP_EncryptInit_ex(_aesEncryptCtx, EVP_aes_256_cbc(), NULL, _aesKey, _aesIV)) {
    throw CryptError("Error : Initialization of the AES encryption context failed.");
  }
  ifs.open(file.c_str(), std::ifstream::ate | std::ifstream::binary);
  ifs.seekg(0, std::ifstream::beg);
  if (ifs.read(buffer.data(), fileContentSize)) {
    if (!EVP_EncryptUpdate(_aesEncryptCtx, fileEncryptedContent, &bytesWritten, reinterpret_cast<unsigned char *>(buffer.data()), fileContentSize)) {
      throw CryptError("Error : an update on the AES encryption failed.");
    }
    bytesOfDataEncrypted += bytesWritten;
    std::cout << "After encrypt update -- file : " << file << ", content size : " << fileContentSize << ", bytes of data encrypted : " << bytesOfDataEncrypted << std::endl;
    if (!EVP_EncryptFinal_ex(_aesEncryptCtx, reinterpret_cast<unsigned char *>(buffer.data()) + bytesOfDataEncrypted, &bytesWritten)) {
      throw CryptError("Error : the AES encryption of the remaining data failed.");
    }
    std::cout << "After final encrypt -- file : " << file << ", content size : " << fileContentSize << ", bytes of data encrypted : " << bytesWritten << std::endl;
  } else {
    return (std::cerr << "Error : could not read the content of the file " << file << std::endl, 0);
  }
  EVP_CIPHER_CTX_cleanup(_aesEncryptCtx);
  delete[] fileEncryptedContent;
  ifs.close();
  return (0);
}

int Crypt::AESDecrypt()
{
  return (0);
}
