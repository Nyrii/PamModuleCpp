//
// Container.hpp for Container in /Users/noboud_n/Documents/Share/PamModuleCpp/inc/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 13:33:28 2016 Nyrandone Noboud-Inpeng
// Last update Sat Oct  8 15:48:23 2016 Nyrandone Noboud-Inpeng
//

#ifndef CONTAINER_HPP_
# define CONTAINER_HPP_

# include <sys/types.h>
# include <string>

using namespace std;

class Container {
public:
  Container();
  ~Container();

  int     open(const string &user);
  int     close(const string &user);

private:

  int       mountIt();
  int       makeDir();
  int       makeLoop();
  int       generatePaths(const string &);

  string    _mountPoint;
  string    _container;
  string    _fileSystem;
  string    _user;
};

#endif /* !CONTAINER_HPP_ */
