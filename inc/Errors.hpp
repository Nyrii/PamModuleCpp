//
// Errors.hpp for Errors in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 15:26:05 2016 Nyrandone Noboud-Inpeng
// Last update Tue Oct 11 16:31:22 2016 Nyrandone Noboud-Inpeng
//

#ifndef ERRORS_HPP_
# define ERRORS_HPP_

# include <stdexcept>
# include <iostream>

# define ERR_LOGIN    "Error : could not get the user login."
# define ERR_MEMALLOC "Error : memory allocation failed."

class			Error : public std::exception
{
public:
  Error() {};
  ~Error() throw() {};

  virtual char const	*what() const throw() { return (_message.c_str()); };
protected:
  std::string		_message;
};

class			MemoryAllocError : public Error
{
public:
  MemoryAllocError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~MemoryAllocError() throw() {};
};

class			CryptError : public Error
{
public:
  CryptError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~CryptError() throw() {};
};

class			CommonError : public Error
{
public:
  CommonError(std::string const &message = "An error occured.") { _message = message; };
  virtual		~CommonError() throw() {};
};

#endif /* ERRORS_HPP_ */
