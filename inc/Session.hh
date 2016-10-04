/*
** Session.hpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:25:41 2016 wilmot_g
** Last update Tue Oct 04 13:55:36 2016 wilmot_g
*/

#include <security/pam_appl.h>
// #include <security/pam_misc.h>
#include <string>

using namespace std;

class   Session {
public:
  Session();
  ~Session();

  int init(pam_handle_t *, int, int, const char **);
private:
    bool        _silent;
    string      _username;
    string      _container;
    string      _volume;
    string      _loopdevice;
    string      _keyfile;
    // t_mntinfo	  mountinfo;
};
