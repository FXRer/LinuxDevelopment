/*
The software in this package is distributed under the GNU General
Public License version 2 (with a special exception described below).

A copy of GNU General Public License (GPL) is included in this distribution,
in the file COPYING.GPL.

As a special exception, if other files instantiate templates or use macros
or inline functions from this file, or you compile this file and link it
with other works to produce a work based on this file, this file
does not by itself cause the resulting work to be covered
by the GNU General Public License.

However the source code for this file must still be made available
in accordance with section (3) of the GNU General Public License.

This exception does not invalidate any other reasons why a work based
on this file might be covered by the GNU General Public License.
*/
/** @file
 *
 * (c) Copyright 2007 by Intra2net AG
 */

#ifndef __ASYNC_PIPE_HPP__
#define __ASYNC_PIPE_HPP__

#include "async_io.hpp"

namespace AsyncIo
{


class SimplePipe : public IOImplementation
{
   public:
      SimplePipe();
      virtual ~SimplePipe();

      bool makePipe(SimplePipe& peer);

      void sendString(const std::string& data);

      boost::signal<void(const std::string&)> signal_received_string;

   protected:

   private:

      void slotReceived();

}; // eo SimplePipe


} // eo namespace AsyncIo


#endif
