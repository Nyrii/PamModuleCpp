//
// Crypt.cpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Sat Oct  8 15:49:06 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct 11 11:02:26 2016 Nyrandone Noboud-Inpeng
//

#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
  } catch (Error &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }

  if (!EVP_EncryptInit_ex(_aesEncryptCtx, EVP_aes_256_cbc(), NULL, _aesKey, _aesIV)
      || !EVP_DecryptInit_ex(_aesDecryptCtx, EVP_aes_256_cbc(), NULL, _aesKey, _aesIV)) {
    throw CryptError("Error : Initialization of the AES decryption context failed.");
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

int                 Crypt::getFileContentSize(const std::string &file) {
  std::ifstream     ifs;
  int               size;

  ifs.open(file.c_str(), std::ifstream::in | std::ifstream::ate | std::ifstream::binary);
  ifs.seekg(0, ifs.end);
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

int                 Crypt::AESEncrypt(const std::string &file)
{
  unsigned char     *fileEncryptedContent;
  int               writtenBytes = 0;
  int               bytesOfDataEncrypted = 0;
  int               fileContentSize = getFileContentSize(file);
  std::ifstream     ifs;
  unsigned char     *buffer;

  if (fileContentSize == -1) {
    return (std::cerr << "The file " << file << " is currently empty : encryption is impossible." << std::endl, 0);
  }
  if (!(buffer = new unsigned char[AES_BLOCK_SIZE + fileContentSize])
      || !(fileEncryptedContent = new unsigned char[AES_BLOCK_SIZE + fileContentSize + 1])) {
    throw MemoryAllocError("Error : could not allocate memory.");
  }
  if (!EVP_EncryptInit_ex(_aesEncryptCtx, NULL, NULL, NULL, NULL)) {
    throw CryptError("Error : Initialization of the AES encryption context failed.");
  }
  ifs.open(file.c_str(), std::ios::binary);
  ifs.seekg(0);
  if (ifs.read(reinterpret_cast<char *>(buffer), fileContentSize)) {
    if (!EVP_EncryptUpdate(_aesEncryptCtx, fileEncryptedContent, &writtenBytes, buffer, fileContentSize)) {
      throw CryptError("Error : an update on the AES encryption failed.");
    }
    bytesOfDataEncrypted += writtenBytes;
    std::cout << "After encrypt update -- file : " << file << ", content size : " << fileContentSize << ", bytes of data encrypted : " << writtenBytes << std::endl;
    if (!EVP_EncryptFinal_ex(_aesEncryptCtx, fileEncryptedContent + bytesOfDataEncrypted, &writtenBytes)) {
      throw CryptError("Error : the AES encryption of the remaining data failed.");
    }
    std::cout << "After final encrypt -- file : " << file << ", content size : " << fileContentSize << ", bytes of data encrypted : " << writtenBytes << std::endl;
  } else {
    return (std::cerr << "Error : could not read the content of the file " << file << " to encrypt it." << std::endl, 0);
  }
  fileEncryptedContent[writtenBytes + bytesOfDataEncrypted] = '\0';

  std::ofstream myfile;
  myfile.open("example.txt");
  myfile << fileEncryptedContent;
  myfile.close();

  AESDecrypt("example.txt");

  delete[] fileEncryptedContent;
  delete[] buffer;
  ifs.close();
  return (0);
}
#include <cstring>

int Crypt::AESDecrypt(const std::string &fileToDecrypt)
{
  unsigned char     *fileDecryptedContent;
  int               writtenBytes = 0;
  int               bytesOfDataDecrypted = 0;
  int               fileContentSize = getFileContentSize(fileToDecrypt);
  std::ifstream     ifs;
  unsigned char     *buffer;
  struct stat       buf;

  ERR_load_crypto_strings();

  if (fileContentSize == -1 || stat(fileToDecrypt.c_str(), &buf) == -1) {
    return (std::cerr << "The file " << fileToDecrypt << " is currently empty : decryption is impossible." << std::endl, 0);
  }
  if (!(buffer = new unsigned char[AES_BLOCK_SIZE + fileContentSize])
      || !(fileDecryptedContent = new unsigned char[AES_BLOCK_SIZE + fileContentSize + 1])) {
    throw MemoryAllocError("Error : could not allocate memory.");
  }
  if (!EVP_DecryptInit_ex(_aesDecryptCtx, NULL, NULL, NULL, NULL)) {
    throw CryptError("Error : Initialization of the AES decryption context failed.");
  }
  ifs.open(fileToDecrypt.c_str(), std::ios::binary);
  ifs.seekg(0);
  if (ifs.read(reinterpret_cast<char *>(buffer), fileContentSize)) {
    if (!EVP_DecryptUpdate(_aesDecryptCtx, fileDecryptedContent, &writtenBytes, buffer, buf.st_size)) {
      throw CryptError("Error : an update on the AES decryption failed.");
    }
    if (!EVP_DecryptFinal_ex(_aesDecryptCtx, fileDecryptedContent + writtenBytes, &bytesOfDataDecrypted)) {
      ERR_print_errors_fp(stderr);
      throw CryptError("Error : the AES decryption of the remaining data failed.");
    }
  } else {
    return (std::cerr << "Error : could not read the content of the file " << fileToDecrypt << " to decrypt it." << std::endl, 0);
  }
  fileDecryptedContent[writtenBytes + bytesOfDataDecrypted - 1] = '\0';
  std::cout << fileDecryptedContent << std::endl;
  delete[] fileDecryptedContent;
  delete[] buffer;
  ifs.close();
  return (0);
}
