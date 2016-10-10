//
// Container.cpp for Container in /Users/noboud_n/Documents/Share/PamModuleCpp/src/
//
// Made by Nyrandone Noboud-Inpeng
// Login   <noboud_n@epitech.eu>
//
// Started on  Tue Oct  4 14:59:30 2016 Nyrandone Noboud-Inpeng
// Last update Sat Oct  8 15:49:14 2016 Nyrandone Noboud-Inpeng
//

#include <sys/stat.h>
#include <sys/mount.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Container.hpp"
#include "Logger.hpp"

Container::Container() {}
Container::~Container() {}

int           Container::makeDir() {
  struct stat st;

  memset(&st, 0, sizeof(st));
  if (stat(_mountPoint.c_str(), &st) == 0)
    return (Logger::get() << Logger::DEBUG << "MountPoint " << "\"" << _mountPoint << "\"" << " already exists" << Logger::endl(), 0);
  if (mkdir(_mountPoint.c_str(), (S_IRWXU | S_IXGRP | S_IXOTH)) == 0)
    return (Logger::get() << Logger::SUCCESS << "Successfully created MountPoint " << "\"" << _mountPoint << "\"" << Logger::endl(), 0);
  return (Logger::get() << Logger::CRITICAL << "Unable to create MountPoint " << "\"" << _mountPoint << "\"" << Logger::endl(), -1);
}

void          Container::generatePaths(const string &user) {
  _user = user;
  _mountPoint = "/home/" + _user + "/Secret";
  _container = "/dev/";
  Logger::get() << Logger::DEBUG << "MountPoint : " << "\"" << _mountPoint << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "Container : " << "\"" << _container << "\"" << Logger::endl();
}

int           Container::mountIt() {
  if (mount(_container.c_str(), _mountPoint.c_str(), _fileSystem.c_str(), 0, NULL) != 0)
    return (Logger::get() << Logger::CRITICAL << "Unable to mount the container" << Logger::endl(), -1);

  struct passwd	*infos;
  if (!(infos = getpwnam(_user.c_str())) || chown(_mountPoint.c_str(), infos->pw_uid, infos->pw_gid) == -1)
    return (Logger::get() << Logger::CRITICAL << "Unable to grant permissions for " << _user << Logger::endl(), -1);
  return (0);
}

int           Container::open(const string &user) {
  generatePaths(user);
  if (makeDir() == -1 || mountIt() == -1)
    return (-1);
  return (0);
}

int           Container::close(const string &user) {
  generatePaths(user);
  if (umount(_mountPoint.c_str()) == -1 || rmdir(_mountPoint.c_str()) == -1)
    return (-1);
  return (0);
}
