//
// AESCrypt.cpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:28:50 2016 Nyrandone Noboud-Inpeng
// Last update Wed Oct 12 14:34:22 2016 Nyrandone Noboud-Inpeng
//

#include <crypto++/filters.h>
#include <crypto++/modes.h>
#include <crypto++/eax.h>
#include <crypto++/files.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "AESCrypt.hpp"
#include "Errors.hpp"

int                   AESCrypt::init() {
  try {
    _aesKey.New(AES_KEYLEN);
    _aesIV.New(AES_KEYLEN);
    _randomGenerator.GenerateBlock(_aesKey, _aesKey.size());
    _randomGenerator.GenerateBlock(_aesIV, _aesIV.size());
  } catch (CryptoPP::Exception &e) {
    cerr << e.what() << endl;
    return (-1);
  }
  return (0);
}

int                     AESCrypt::encrypt(const string &file) {
  EAX<AES>::Encryption  encryption;
  string                encryptedFile = "crypt.txt";

  try {
    encryption.SetKeyWithIV(_aesKey, _aesKey.size(), _aesIV);
    FileSource fs1(file.c_str(), true,
                    new AuthenticatedEncryptionFilter(encryption,
                                                      new FileSink(encryptedFile.c_str())));
  } catch (Exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}

int                     AESCrypt::decrypt(const string &fileToDecryptName, const string &finalFileName,
                                          int const previousSize) {
  EAX<AES>::Decryption  decryption;
  ofstream              finalFile;
  ifstream              tmpFile;
  std::vector<char>     buffer(DL_BYTES);
  int                   bytesDownloaded = 0;

  try {
    decryption.SetKeyWithIV(_aesKey, _aesKey.size(), _aesIV);
    FileSource fs1(fileToDecryptName.c_str(), true,
                  new AuthenticatedEncryptionFilter(decryption, new FileSink("tmp")));
  } catch (Exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  finalFile.open(finalFileName.c_str());
  tmpFile.open("tmp");
  tmpFile.seekg(0, std::ios::beg);
  if (tmpFile.is_open()) {
    while (tmpFile.read(buffer.data(), bytesDownloaded < previousSize - DL_BYTES ?
                                        DL_BYTES : previousSize - bytesDownloaded)) {
      if (finalFile.is_open()) {
        finalFile.write(buffer.data(), bytesDownloaded < previousSize - DL_BYTES ?
                                        DL_BYTES : previousSize - bytesDownloaded);
      } else {
        finalFile.close();
        tmpFile.close();
        throw CommonError("Error : the destination file cannot receive the decrypted content.");
      }
      bytesDownloaded += DL_BYTES;
    }
  } else {
    finalFile.close();
    tmpFile.close();
    throw CommonError("Error : decryption cannot be done due to an unexisting or empty file.");
  }
  finalFile.close();
  tmpFile.close();
  remove("tmp");
  remove("crypt.txt");
  return (0);
}
