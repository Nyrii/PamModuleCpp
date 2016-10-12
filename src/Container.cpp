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
#include <errno.h>
#include "Container.hpp"
#include "Logger.hpp"

Container::Container() {}
Container::~Container() {}

ostream       &operator<<(ostream &os, const Container &c) {
  Logger::get() << Logger::DEBUG << "User       : " << "\"" << c.getUser() << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "Container  : " << "\"" << c.getContainer() << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "FileSystem : " << "\"" << c.getFileSystem() << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "LoopDevice : " << "\"" << c.getLoopDevice() << "\"" << Logger::endl();
  Logger::get() << Logger::DEBUG << "MountPoint : " << "\"" << c.getMountPoint() << "\"" << Logger::endl();
  return (os);
}

int           Container::makeMountPoint() const {
  if (access(_mountPoint.c_str(), R_OK) == 0)
    return (Logger::get() << Logger::SUCCESS << "MountPoint already exists" << Logger::endl(), 0);
  if (mkdir(_mountPoint.c_str(), (S_IRWXU | S_IXGRP | S_IXOTH)) == 0)
    return (Logger::get() << Logger::SUCCESS << "Successfully created MountPoint" << Logger::endl(), 0);
  return (Logger::get() << Logger::CRITICAL << "Unable to create MountPoint" << Logger::endl(), -1);
}

int          Container::attachLoop() const {
  int        fdContainer;
  int			   fd;
  int        ret;

  if ((fd = ::open(_loopDevice.c_str(), O_RDWR)) == -1 || (fdContainer = ::open(_container.c_str(), O_RDWR)) == -1) {
    if (fd != -1)
      ::close(fd);
    return (Logger::get() << Logger::CRITICAL << "Unable to attach to loopDevice" << Logger::endl(), -1);
  }
  ret = ioctl(fd, LOOP_SET_FD, fdContainer);
  ::close(fdContainer);
  if (ret == -1)
    return (::close(fd), Logger::get() << Logger::CRITICAL << "Unable to attach to loopDevice" << Logger::endl(), -1);
  Logger::get() << Logger::SUCCESS << "Container attached to loopDevice" << Logger::endl();

  struct loop_info64  info;

  memset(&info, 0, sizeof(info));
  strncpy((char *)info.lo_file_name, _container.c_str(), LO_NAME_SIZE);
  if (ioctl(fd, LOOP_SET_STATUS64, &info) == -1)
    return (::close(fd), Logger::get() << Logger::WARN << "Unable to set loopDevice infos" << Logger::endl(), -1);
  return (Logger::get() << Logger::SUCCESS << "loopDevice infos updated" << Logger::endl(), 0);
}

int          Container::detachLoop() const {
  int		     fd;

  if ((fd = ::open(_loopDevice.c_str(), O_RDWR)) == -1)
    return (Logger::get() << Logger::WARN << "Unable to open loop device" << Logger::endl(), -1);
  if (ioctl(fd, LOOP_CLR_FD) < 0)
    return (::close(fd), Logger::get() << Logger::WARN << "Unable to detach loop device : " << strerror(errno) << Logger::endl(), -1);
  ::close(fd);
  return (Logger::get() << Logger::SUCCESS << "loopDevice detached" << Logger::endl(), 0);
}

int          Container::generatePaths(const string &user) {
  char       buffer[15];
  int   		 nb;
  int        fd;

  if ((fd = ::open("/dev/loop-control", O_RDONLY)) == -1)
    return (Logger::get() << Logger::CRITICAL << "Unable to find free loop device" << Logger::endl(), -1);
  if ((nb = ioctl(fd, LOOP_CTL_GET_FREE)) < 0)
    return (::close(fd), Logger::get() << Logger::CRITICAL << "Unable to find free loop device" << Logger::endl(), -1);
  ::close(fd);
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, 15, "%s%d", "/dev/loop", nb);
  _loopDevice = string(buffer);
  _user = user;
  _container = "/root/cntr/" + _user + ".img";
  _mountPoint = "/home/" + _user + "/secret";
  _fileSystem = "ext4";
  cout << *this;
  return (0);
}

int           Container::mount() const {
  if (::mount(_loopDevice.c_str(), _mountPoint.c_str(), _fileSystem.c_str(), 0, NULL) != 0)
    return (Logger::get() << Logger::CRITICAL << "Unable to mount the container" << Logger::endl(), -1);
  Logger::get() << Logger::SUCCESS << "Container mounted" << Logger::endl();

  struct passwd	*infos;
  if (!(infos = getpwnam(_user.c_str())) || chown(_mountPoint.c_str(), infos->pw_uid, infos->pw_gid) == -1)
    return (Logger::get() << Logger::WARN << "Unable to grant permissions for " << _user << Logger::endl(), -1);
  Logger::get() << Logger::SUCCESS << "Permissions granted" << Logger::endl();
  return (0);
}

int           Container::open(const string &user) {
  return (generatePaths(user) == -1 || makeMountPoint() == -1 || attachLoop() == -1 || mount() == -1 ? -1 : 0);
}

int           Container::findLoopDevice() {
  char        buffer[15];
  int   		  i;
  int         fd;
  struct loop_info64  info;

  for (i = 0; ; i++) {
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, 15, "%s%d", "/dev/loop", i);
    if ((fd = ::open(buffer, O_RDONLY)) == -1 && i >= 10)
      return (Logger::get() << Logger::WARN << "Unable to find the device" << Logger::endl(), 0);
    if (fd != -1) {
      if (ioctl(fd, LOOP_GET_STATUS64, &info) == 0)
        if (string((char *)info.lo_file_name) == _container) {
          memset(buffer, 0, sizeof(buffer));
          snprintf(buffer, 15, "%s%d", "/dev/loop", i);
          _loopDevice = string(buffer);
          ::close(fd);
          return (0);
        }
        ::close(fd);
    }
  }
  return (Logger::get() << Logger::WARN << "Unable to find the device" << Logger::endl(), 0);
}

int           Container::close(const string &user) {
  if (generatePaths(user) == -1 || findLoopDevice() == -1)
    return (-1);
  if (access(_mountPoint.c_str(), R_OK) != 0)
    Logger::get() << Logger::WARN << "MountPoint already deleted" << Logger::endl();
  else {
    if (umount2(_mountPoint.c_str(), MNT_FORCE) == -1)
      return (Logger::get() << Logger::CRITICAL << "Unable to unmount container" << Logger::endl(), -1);
    Logger::get() << Logger::SUCCESS << "Container unmounted" << Logger::endl();
    rmdir(_mountPoint.c_str()) == -1 ?
      Logger::get() << Logger::WARN << "Unable to delete directory" << Logger::endl() :
      Logger::get() << Logger::SUCCESS << "MountPoint deleted" << Logger::endl();
  }
  return (detachLoop() == -1);
}
