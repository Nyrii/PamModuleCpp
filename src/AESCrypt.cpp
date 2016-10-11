//
// AESCrypt.cpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:28:50 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct 11 18:03:11 2016 Nyrandone Noboud-Inpeng
//

#include <crypto++/filters.h>
#include <crypto++/modes.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "AESCrypt.hpp"
#include "Errors.hpp"

int                   AESCrypt::init() {
  try {
    _randomGenerator.GenerateBlock(_aesKey, _aesKey.size());
    _randomGenerator.GenerateBlock(_aesIV, AES::BLOCKSIZE);
  } catch (CryptoPP::Exception &e) {
    cerr << e.what() << endl;
    return (-1);
  }
  return (0);
}

int                   AESCrypt::encrypt(const string &file) {
  unsigned char       *buffer;
  int                 fileSize;
  ifstream            ifs;
  ofstream            tmp;

  if ((fileSize = getFileContentSize(file)) == -1) {
    throw CommonError("Error : " + file + " is actually empty : the encryption is impossible.");
  }
  if (!(buffer = new unsigned char[fileSize + 1]) || !memset(buffer, 0, fileSize + 1)) {
    throw MemoryAllocError("Error : could not allocate memory.");
  }
  ifs.open(file.c_str(), ifstream::in | ifstream::ate | ifstream::binary);
  ifs.seekg(0, ios::beg);
  if (ifs.read(reinterpret_cast<char *>(buffer), fileSize)) {
    try {
      CFB_Mode<AES>::Encryption cfbEncryption(_aesKey, _aesKey.size(), _aesIV);
      cfbEncryption.ProcessData(buffer, buffer, fileSize);
    } catch (CryptoPP::Exception &e) {
      cerr << e.what() << endl;
    }
    cout << buffer << endl;
    tmp.open("crypt.txt");
    tmp << buffer;
    tmp.close();
  }
  ifs.close();
  delete[] buffer;
  return (0);
}

int                   AESCrypt::decrypt(const string &file, int const previousSize) {
  unsigned char       *buffer;
  ifstream            ifs;
  struct stat         info;
  ofstream            tmp;

  if (!(buffer = new unsigned char[previousSize + 4096])) {
    throw MemoryAllocError("Error : could not allocate memory.");
  }
  if (stat(file.c_str(), &info) == -1) {
    throw CommonError("Error: could not get the information of " + file);
  }
  ifs.open(file.c_str(), ifstream::in | ifstream::ate | ifstream::binary);
  ifs.seekg(0, ios::beg);
  if (ifs.read(reinterpret_cast<char *>(buffer), info.st_size)) {
    try {
      CFB_Mode<AES>::Decryption cfbDecryption(_aesKey, _aesKey.size(), _aesIV);
      cfbDecryption.ProcessData(buffer, buffer, previousSize);
    } catch (CryptoPP::Exception &e) {
      cerr << e.what() << endl;
      return (-1);
    }
    tmp.open("decrypt.txt");
    tmp << buffer;
    tmp.close();
  } else {
    throw CommonError("Error : could not access " + file);
  }
  ifs.close();
  delete[] buffer;
  return (0);
}
