#ifndef PV_H
#define PV_H

#include <string>

////////////////////////////////////////////////////////////////////////////////
class Pv
{
public:
   Pv(std::string const &store);
   ~Pv() = default;

   Pv(Pv const&) = delete;
   Pv &operator=(Pv const&) = delete;
   Pv(Pv&&) = delete;
   Pv &operator=(Pv&&) = delete;

   void initialize();
   void add(std::string const &site);
   void get(std::string const &site);

private:
   std::string const &m_store;
};

#endif // PV_H
