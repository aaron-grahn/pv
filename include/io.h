#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////
namespace Io
{
   /////////////////////////////////////////////////////////////////////////////
   enum class Encoding : int
   {
      Hex,
      Base64,
   };

   /////////////////////////////////////////////////////////////////////////////
   namespace Istream
   {
      //////////////////////////////////////////////////////////////////////////
      class Byte
      {
      protected: 
         Byte(std::istream &is);

      public:
         virtual ~Byte() = default;

         Byte(Byte const&) = default;
         Byte &operator=(Byte const&) = default;
         Byte(Byte&&) = default;
         Byte &operator=(Byte&&) = default;

         Buffer read();

      private:
         std::istream &m_is;

         virtual Buffer decode(std::string const &data) = 0;
      };

      //////////////////////////////////////////////////////////////////////////
      class Hex : public Byte
      {
      public:
         Hex(std::istream &is);
         virtual ~Hex() = default;

         Hex(Hex const&) = default;
         Hex &operator=(Hex const&) = default;
         Hex(Hex&&) = default;
         Hex &operator=(Hex&&) = default;

      private:
         virtual Buffer decode(std::string const &data) override;
      };

      //////////////////////////////////////////////////////////////////////////
      class Base64 : public Byte
      {
      public:
         Base64(std::istream &is);
         virtual ~Base64() = default;

         Base64(Base64 const&) = default;
         Base64 &operator=(Base64 const&) = default;
         Base64(Base64&&) = default;
         Base64 &operator=(Base64&&) = default;

      private:
         virtual Buffer decode(std::string const &data) override;
      };
   } // namespace Istream

   /////////////////////////////////////////////////////////////////////////////
   namespace Ostream
   {
      //////////////////////////////////////////////////////////////////////////
      class Byte
      {
      protected: 
         Byte(std::ostream &os);

      public:
         virtual ~Byte() = default;

         Byte(Byte const&) = default;
         Byte &operator=(Byte const&) = default;
         Byte(Byte&&) = default;
         Byte &operator=(Byte&&) = default;

         void write(Buffer const &data);

      private:
         virtual std::string encode(Buffer const &data) = 0;

         std::ostream &m_os;
      };

      //////////////////////////////////////////////////////////////////////////
      class Hex : public Byte
      {
      public:
         Hex(std::ostream &os);
         virtual ~Hex() = default;

         Hex(Hex const&) = default;
         Hex &operator=(Hex const&) = default;
         Hex(Hex&&) = default;
         Hex &operator=(Hex&&) = default;

      private:
         virtual std::string encode(Buffer const &data) override;
      };

      //////////////////////////////////////////////////////////////////////////
      class Base64 : public Byte
      {
      public:
         Base64(std::ostream &os);
         virtual ~Base64() = default;

         Base64(Base64 const&) = default;
         Base64 &operator=(Base64 const&) = default;
         Base64(Base64&&) = default;
         Base64 &operator=(Base64&&) = default;

      private:
         virtual std::string encode(Buffer const &data) override;
      };
   } // namespace Ostream
} // namespace Io

////////////////////////////////////////////////////////////////////////////////
Io::Ostream::Byte &operator<<(std::ostream &os, Io::Encoding enc);

////////////////////////////////////////////////////////////////////////////////
Io::Istream::Byte &operator>>(std::istream &os, Io::Encoding enc);

#endif // IO_H
