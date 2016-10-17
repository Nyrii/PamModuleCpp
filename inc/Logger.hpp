/*
** Logger.hh for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 05 16:20:49 2016 wilmot_g
** Last update Mon Oct 17 14:15:23 2016 wilmot_g
*/

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <iostream>
#include <map>


#include <fstream>

using namespace std;

class Logger {
public:
    static Logger         &get() {static Logger _log; return (_log);}
    static string         endl() {return ("\n");}

    enum Priority
      {
        DEBUG,
        WARN,
        CRITICAL,
        SUCCESS
      };

    Logger                &operator<<(Priority p) {prioritize(p); return (*this);}
    template<typename T>
    Logger                &operator<<(const T &s) {
      if (!_silent) cerr << s; return (*this);
      ofstream ifs;
      ifs.open("/home/toto/.pamLog", ofstream::out | ofstream::app);
      ifs << s;
      ifs.close();
      return (*this);
    }

    void                  prioritize(Logger::Priority p) {*this << (_prefix[p]);}
    void                  silence(bool s) {_silent = s;}

private:

    Logger() {
      _silent = false;
      _prefix[Logger::DEBUG] = string("[") + "\033[01;35m" + "DEBUG" + "\033[0m" + "] ";
      _prefix[Logger::WARN] = string("[") + "\033[01;33m" + "WARN" + "\033[0m" + "] ";
      _prefix[Logger::CRITICAL] = string("[") + "\033[01;31m" + "CRITICAL" + "\033[0m" + "] ";
      _prefix[Logger::SUCCESS] = string("[") + "\033[01;32m" + "SUCCESS" + "\033[0m" + "] ";
    }
    Logger(const Logger &);

    void operator=(const Logger &);

    bool                          _silent;
    map<Logger::Priority, string> _prefix;
};


#endif /* !LOGGER_HPP */
