//
// AESCrypt.cpp for AESCrypt in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:28:50 2016 Nyrandone Noboud-Inpeng
// Last update Wed Oct 12 17:42:26 2016 Nyrandone Noboud-Inpeng
//

#include <crypto++/filters.h>
#include <crypto++/modes.h>
#include <crypto++/eax.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "AESCrypt.hpp"
#include "Errors.hpp"

int                                 AESCrypt::init() {
  string                            tmpKey;
  string                            tmpIV;
  try {
    _aesKey.New(AES_KEYLEN);
    _aesIV.New(AES_KEYLEN);
    _randomGenerator.GenerateBlock(_aesKey, _aesKey.size());
    _randomGenerator.GenerateBlock(_aesIV, _aesIV.size());
    StringSource storeKeyInString(_aesKey.data(), _aesKey.size(), true, new StringSink(tmpKey));
    StringSource storeIVInString(_aesIV.data(), _aesIV.size(), true, new StringSink(tmpIV));
    StringSource storeKeyInFile(tmpKey, true, new FileSink(KEY_FILE));
    StringSource storeIVInFile(tmpIV, true, new FileSink(IV_FILE));
  } catch (CryptoPP::Exception &e) {
    cerr << e.what() << endl;
    return (-1);
  }
  return (0);
}

int                               AESCrypt::encrypt(const string &file) {
  EAX<AES>::Encryption            encryption;
  string                          encryptedFile = "crypt.txt";

  try {
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

int                               AESCrypt::decrypt(const string &fileToDecryptName, const string &finalFileName,
                                                    int const previousSize) {
  EAX<AES>::Decryption            decryption;
  ofstream                        finalFile;
  ifstream                        tmpFile;
  std::vector<unsigned char>      buffer(DL_BYTES);
  int                             bytesDownloaded = 0;

  try {
    decryption.SetKeyWithIV(_aesKey, _aesKey.size(), _aesIV);
    FileSource decrypt(fileToDecryptName.c_str(), true,
                      new AuthenticatedEncryptionFilter(decryption, new FileSink("tmp")));
  } catch (Exception &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
  finalFile.open(finalFileName.c_str());
  tmpFile.open("tmp");
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
  remove("tmp");
  // remove("crypt.txt");
  return (0);
}

int                               AESCrypt::readKeys() {
  ifstream                        aesKeyFile;
  ifstream                        aesIVFile;
  std::vector<unsigned char>      keyBuffer(AES_KEYLEN);
  std::vector<unsigned char>      IVBuffer(AES_KEYLEN);

  _aesKey.New(AES_KEYLEN);
  _aesIV.New(AES_KEYLEN);
  aesKeyFile.open(KEY_FILE);
  aesIVFile.open(IV_FILE);
  if (!aesKeyFile.is_open() || !aesIVFile.is_open()
      || !aesKeyFile.read(reinterpret_cast<char *>(keyBuffer.data()), _aesKey.size())
      || !aesIVFile.read(reinterpret_cast<char *>(IVBuffer.data()), _aesIV.size())) {
    throw CommonError("Error : could not open the AES key or IV File.");
  }
  std::copy(keyBuffer.begin(), keyBuffer.end(), _aesKey.data());
  std::copy(IVBuffer.begin(), IVBuffer.end(), _aesIV.data());
  return (0);
}
