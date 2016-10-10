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
#include <sys/ioctl.h>
#include <linux/loop.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "Container.hpp"
#include "Logger.hpp"

Container::Container() {}
Container::~Container() {}

int           Container::makeDir() {
  if (access(_mountPoint.c_str(), R_OK) == 0)
    return (Logger::get() << Logger::DEBUG << "MountPoint already exists" << Logger::endl(), 0);
  if (mkdir(_mountPoint.c_str(), (S_IRWXU | S_IXGRP | S_IXOTH)) == 0)
    return (Logger::get() << Logger::SUCCESS << "Successfully created MountPoint" << Logger::endl(), 0);
  return (Logger::get() << Logger::CRITICAL << "Unable to create MountPoint" << Logger::endl(), -1);
}

int          Container::makeLoop() {
  return (0);
}

int          Container::generatePaths(const string &user) {
  char       buffer[15];
  int   		 nb;
  int        fd;

  if ((fd = ::open("/dev/loop-control", O_RDONLY)) == -1)
    return (Logger::get() << Logger::CRITICAL << "Unable to find free loop device" << Logger::endl(), -1);
    if ((nb = ioctl(fd, LOOP_CTL_GET_FREE)) < 0) {
      ::close(fd);
      return (Logger::get() << Logger::CRITICAL << "Unable to find free loop device" << Logger::endl(), -1);
    }
  ::close(fd);
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, 15, "%s%d", "/dev/loop", nb);
  _container = string(buffer);
  _user = user;
  _mountPoint = "/home/" + _user + "/Secret";
  Logger::get() << Logger::DEBUG << "MountPoint : " << "\"" << _mountPoint << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "Container : " << "\"" << _container << "\"" << Logger::endl();
  return (0);
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
  return (generatePaths(user) == -1 || makeDir() == -1 || mountIt() == -1 ? -1 : 0);
}

int           Container::close(const string &user) {
  if (generatePaths(user) == -1)
    return (-1);
  if (umount(_mountPoint.c_str()) == -1)
    return (Logger::get() << Logger::CRITICAL << "Unable to unmount container" << Logger::endl(), -1);
  if (rmdir(_mountPoint.c_str()) == -1)
    return (Logger::get() << Logger::WARN << "Unable to delete directory" << Logger::endl(), -1);
  return (0);
}
