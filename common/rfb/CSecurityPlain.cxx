/* Copyright (C) 2005 Martin Koegler
 * Copyright (C) 2010 TigerVNC Team
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <rfb/CConnection.h>
#include <rfb/CSecurityPlain.h>

#include <rdr/OutStream.h>

using namespace rfb;

bool CSecurityPlain::processMsg()
{
   rdr::OutStream* os = cc->getOutStream();

  std::string username;
  std::string password;

  cc->getUserPasswd(cc->isSecure(), &username, &password);

  // Return the response to the server
  os->writeU32(username.size());
  os->writeU32(password.size());
  os->writeBytes((const uint8_t*)username.data(), username.size());
  os->writeBytes((const uint8_t*)password.data(), password.size());
  os->flush();
  return true;
}
