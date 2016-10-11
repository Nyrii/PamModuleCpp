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
# include <iostream>

using namespace std;

class     Container {
public:
  Container();
  ~Container();

  int     open(const string &user);
  int     close(const string &user);

  string  getMountPoint() const {return (_mountPoint);}
  string  getLoopDevice() const {return (_loopDevice);}
  string  getContainer()  const {return (_container);}
  string  getFileSystem() const {return (_fileSystem);}
  string  getUser()       const {return (_user);}

private:

  int     mount();
  int     makeMountPoint();
  int     attachLoop();
  int     detachLoop();
  int     generatePaths(const string &);

  string  _mountPoint;
  string  _loopDevice;
  string  _container;
  string  _fileSystem;
  string  _user;
};

ostream   &operator<<(ostream &, const Container &);

#endif /* !CONTAINER_HPP_ */
