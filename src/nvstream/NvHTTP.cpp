/*
 *      Copyright (C) 2015 Anthony Miyaguchi
 *      Copyright (C) 2015 Team XBMC
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#include "NvHTTP.h"

using namespace std;
using namespace MOONLIGHT;

string getXmlString(string str, string tagname)
{
  return "";
}

string NvHTTP::getServerInfo(string uid)
{
  return "";
}

PairState NvHTTP::getPairState(string serverInfo)
{
  return PairState::FAILED;
}

int NvHTTP::getCurrentGame(string serverInfo)
{
  return -1;
}

PairState NvHTTP::pair(string pin)
{
  return PairState::FAILED;
}

std::string NvHTTP::openHTTPConnection(string url, bool enableReadTimeout)
{
  return "";
}
