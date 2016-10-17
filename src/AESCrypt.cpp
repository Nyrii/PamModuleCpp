//
// AESCrypt.cpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:28:50 2016 Nyrandone Noboud-Inpeng
// Last update Mon Oct 17 13:42:30 2016 Nyrandone Noboud-Inpeng
//

#include <crypto++/filters.h>
#include <crypto++/modes.h>
#include <crypto++/eax.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "AESCrypt.hpp"
#include "Errors.hpp"

int                                 AESCrypt::init(const string &user) {
  string                            tmpKey;
  string                            tmpIV;
  string                            keyFileName(KEY_FILE + user);
  string                            IVFileName(IV_FILE + user);
  try {
    _aesKey.New(AES_KEYLEN);
    _aesIV.New(AES_KEYLEN);
    _randomGenerator.GenerateBlock(_aesKey, _aesKey.size());
    _randomGenerator.GenerateBlock(_aesIV, _aesIV.size());
    StringSource storeKeyInString(_aesKey.data(), _aesKey.size(), true, new StringSink(tmpKey));
    StringSource storeIVInString(_aesIV.data(), _aesIV.size(), true, new StringSink(tmpIV));
    StringSource storeKeyInFile(tmpKey, true, new FileSink(keyFileName.c_str()));
    StringSource storeIVInFile(tmpIV, true, new FileSink(IVFileName.c_str()));
  } catch (Exception &e) {
    cerr << e.what() << endl;
    return (-1);
  }
  return (0);
}

int                               AESCrypt::encrypt(const string &file, const string &user) {
  EAX<AES>::Encryption            encryption;
  string                          encryptedFile(string(ROOT_PATH) + "crypt.txt");
  string                          sizeFileName(ROOT_PATH + string(SIZE_FILE) + user);
  struct stat                     info;
  ofstream                        sizeFile;
  stringstream                    convertSizeToString;

  try {
    if (stat(file.c_str(), &info) == -1) {
      throw CommonError("Error : cannot get informations about " + file);
    }
    sizeFile.open(sizeFileName.c_str());
    if (!sizeFile.is_open()) {
      sizeFile.close();
      throw CommonError("Error : cannot open the size file " + string(sizeFileName));
    }
    convertSizeToString << info.st_size;
    sizeFile << convertSizeToString.str();
    sizeFile.close();
    encryption.SetKeyWithIV(_aesKey, _aesKey.size(), _aesIV);
    FileSource encrypt(file.c_str(), true,
                      new AuthenticatedEncryptionFilter(encryption,
                                                        new FileSink(encryptedFile.c_str())));
  } catch (Exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  return (0);
}

int                               AESCrypt::decrypt(const string &fileToDecryptName,
                                                    const string &finalFileName,
                                                    const string &user) {
  EAX<AES>::Decryption            decryption;
  ofstream                        finalFile;
  ifstream                        tmpFile;
  std::vector<unsigned char>      buffer(DL_BYTES + 1);
  int                             bytesDownloaded = 0;
  int                             previousSize;
  string                          cryptFilePath(string(ROOT_PATH) + "crypt.txt");
  string                          tmpFilePath(string(ROOT_PATH) + "tmp");

  if ((previousSize = getFilePreviousSize(user)) == -1) {
    throw CommonError("Error : cannot get the initial size of the encrypted file.");
  }
  try {
    decryption.SetKeyWithIV(_aesKey, _aesKey.size(), _aesIV);
    FileSource decrypt(fileToDecryptName.c_str(), true,
                      new AuthenticatedEncryptionFilter(decryption, new FileSink(tmpFilePath.c_str())));
  } catch (Exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  finalFile.open(finalFileName.c_str());
  tmpFile.open(tmpFilePath.c_str());
  tmpFile.seekg(0, std::ios::beg);
  if (tmpFile.is_open()) {
    while (tmpFile.read(reinterpret_cast<char *>(buffer.data()), bytesDownloaded < previousSize - DL_BYTES ?
                                                                  DL_BYTES : previousSize - bytesDownloaded)) {
      if (finalFile.is_open()) {
        finalFile.write(reinterpret_cast<char *>(buffer.data()), bytesDownloaded < previousSize - DL_BYTES ?
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
  remove(tmpFilePath.c_str());
  remove(cryptFilePath.c_str());
  return (0);
}

int                               AESCrypt::readKeys(const string &user) {
  ifstream                        aesKeyFile;
  ifstream                        aesIVFile;
  std::vector<unsigned char>      keyBuffer(AES_KEYLEN);
  std::vector<unsigned char>      IVBuffer(AES_KEYLEN);
  string                          keyFileName(ROOT_PATH + string(KEY_FILE) + user);
  string                          IVFileName(ROOT_PATH + string(IV_FILE) + user);

  _aesKey.New(AES_KEYLEN);
  _aesIV.New(AES_KEYLEN);
  aesKeyFile.open(keyFileName.c_str());
  aesIVFile.open(IVFileName.c_str());
  if (!aesKeyFile.is_open() || !aesIVFile.is_open()
      || !aesKeyFile.read(reinterpret_cast<char *>(keyBuffer.data()), _aesKey.size())
      || !aesIVFile.read(reinterpret_cast<char *>(IVBuffer.data()), _aesIV.size())) {
    throw CommonError("Error : could not open the AES key or IV File.");
  }
  std::copy(keyBuffer.begin(), keyBuffer.end(), _aesKey.data());
  std::copy(IVBuffer.begin(), IVBuffer.end(), _aesIV.data());
  return (0);
}

int                               AESCrypt::getFilePreviousSize(const string &user) {
  ifstream                        fileSize;
  struct stat                     info;
  string                          fileSizeName(ROOT_PATH + string(SIZE_FILE) + user);
  if (stat(fileSizeName.c_str(), &info) == -1) {
    return (-1);
  }
  std::vector<char>               buffer(info.st_size + 1);
  int                             size;
  stringstream                    convertStringToInt;

  fileSize.open(fileSizeName.c_str());
  fileSize.seekg(0, std::ios::beg);
  if (fileSize.read(buffer.data(), info.st_size)) {
    convertStringToInt << buffer.data();
    convertStringToInt >> size;
    if (size <= 0) {
      fileSize.close();
      return (-1);
    }
    fileSize.close();
    return (size);
  }
  return (-1);
}
