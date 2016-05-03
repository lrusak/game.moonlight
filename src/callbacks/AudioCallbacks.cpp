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
  static const GAME_AUDIO_CHANNEL channelMap[] = { GAME_CH_FL, GAME_CH_FR, GAME_CH_NULL };
  if (!frontend->OpenAudioStream(GAME_AUDIO_CODEC_OPUS, /* TODO opusConfig->sampleRate ,*/ channelMap))
    frontend = nullptr;
}

void audio_renderer_cleanup()
{
  isyslog("Deinitialize audio");
  if (frontend)
  {
    frontend->CloseStream(GAME_STREAM_AUDIO);
    frontend = NULL;
  }
}

void audio_renderer_decode_and_play_sample(char* sampleData, int sampleLength)
{
  if (frontend)
    frontend->AddStreamData(GAME_STREAM_AUDIO, reinterpret_cast<uint8_t*>(sampleData), sampleLength);
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
