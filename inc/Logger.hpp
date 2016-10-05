/*
** Logger.hh for PamModuleCpp in /home/wilmot_g/Epitech/Crypto/PamModuleCpp/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Wed Oct 05 16:20:49 2016 wilmot_g
** Last update Wed Oct 05 18:04:15 2016 wilmot_g
*/

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <iostream>
#include <map>

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

    Logger                &operator<<(const string &s) {log(s); return (*this);}
    Logger                &operator<<(int i) {log(i); return (*this);}
    Logger                &operator<<(Priority p) {prioritize(p); return (*this);}
    void                  log(const string &);
    void                  log(int);
    void                  prioritize(Logger::Priority);
    void                  silence(bool);

private:

    Logger();
    Logger(const Logger &);

    void operator=(const Logger &);

    bool                          _silent;
    map<Logger::Priority, string> _prefix;
};


#endif /* !LOGGER_HPP */
