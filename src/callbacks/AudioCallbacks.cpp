#include "Callbacks.h"
#include "log/Log.h"
#include "MoonlightEnvironment.h"
#include "kodi/libKODI_game.h"

using namespace MOONLIGHT;

static CHelper_libKODI_game* frontend = NULL;

void audio_renderer_setup(int audioConfiguration, POPUS_MULTISTREAM_CONFIGURATION opusConfig)
{
  isyslog("Initialize audio");
  frontend = CMoonlightEnvironment::Get().GetFrontend();
  if (!frontend->OpenAudioStream(GAME_AUDIO_FORMAT_OPUS, opusConfig->sampleRate, GAME_AUDIO_CHANNEL_UNKNOWN))
    frontend = nullptr;
}

void audio_renderer_cleanup()
{
  isyslog("Deinitialize audio");
  if (frontend)
  {
    frontend->CloseAudioStream();
    frontend = NULL;
  }
}

void audio_renderer_decode_and_play_sample(char* sampleData, int sampleLength)
{
  if (frontend)
    frontend->AddAudioData(reinterpret_cast<uint8_t*>(sampleData), sampleLength);
}

AUDIO_RENDERER_CALLBACKS MOONLIGHT::getAudioCallbacks()
{
  AUDIO_RENDERER_CALLBACKS callbacks
  {
      audio_renderer_setup,
      audio_renderer_cleanup,
      audio_renderer_decode_and_play_sample
  };
  return callbacks;
}
