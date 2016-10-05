/*
** Session.hpp for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Oct 04 13:25:41 2016 wilmot_g
** Last update Wed Oct 05 18:28:15 2016 wilmot_g
*/

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <string>

using namespace std;

class   Session {
public:
  Session();
  ~Session();

  int init(pam_handle_t *);
private:
    string      _username;
    string      _container;
    string      _volume;
    string      _loopdevice;
    string      _keyfile;
    // t_mntinfo	  mountinfo;
};
