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
#include "Callbacks.h"
#include "log/Log.h"
#include "MoonlightEnvironment.h"
#include "kodi/libKODI_game.h"
#include "Limelight.h"

using namespace MOONLIGHT;
using namespace P8PLATFORM;

static CHelper_libKODI_game* frontend = NULL;
static int m_width = 0;
static int m_height = 0;

void decoder_renderer_setup(int width, int height, int redrawRate, void* context, int drFlags)
{
  isyslog("VideoCallbacks::Setup");

  m_width = width;
  m_height = height;
  frontend = CMoonlightEnvironment::Get().GetFrontend();
  if (!frontend->OpenVideoStream(GAME_VIDEO_CODEC_H264/* TODO , width, height */))
    frontend = nullptr;
}

void decoder_renderer_cleanup()
{
  isyslog("VideoCallbacks::Cleanup");

  if (frontend)
  {
    frontend->CloseStream(GAME_STREAM_VIDEO);
    frontend = NULL;
  }
}

int decoder_renderer_submit_decode_unit(PDECODE_UNIT decodeUnit)
{
  if (frontend)
  {
    PLENTRY entry = decodeUnit->bufferList;
    while (entry != NULL)
    {
      frontend->AddStreamData(GAME_STREAM_VIDEO, reinterpret_cast<uint8_t*>(entry->data), entry->length);
      entry = entry->next;
    }
  }

  return DR_OK;
}

DECODER_RENDERER_CALLBACKS MOONLIGHT::getDecoderCallbacks()
{
  DECODER_RENDERER_CALLBACKS callbacks =
  {
      decoder_renderer_setup,
      decoder_renderer_cleanup,
      decoder_renderer_submit_decode_unit
  };
  return callbacks;
}
