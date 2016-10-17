//
// Crypt.hpp for Crypt in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct 11 15:38:09 2016 Nyrandone Noboud-Inpeng
// Last update Mon Oct 17 14:43:39 2016 Nyrandone Noboud-Inpeng
//

#ifndef CRYPT_HPP_
# define CRYPT_HPP_

# include <iostream>
# include <fstream>
# include "ICrypt.hpp"

using namespace std;

class Crypt : ICrypt{

  public:
    virtual               ~Crypt() {};

    virtual int           init(const string &) = 0;
    virtual int           encrypt(const string &, const string &) = 0;
    virtual int           decrypt(const string &, const string &) = 0;

  protected:
    int                   getFileContentSize(const string &file) {
      std::ifstream       ifs;
      int                 size;

      ifs.open(file.c_str(), ifstream::in | ifstream::ate | ifstream::binary);
      ifs.seekg(0, ifs.end);
      size = ifs.tellg();
      ifs.close();
      return (size);
    };
};

#endif /* !CRYPT_HPP_ */
