#include "AudioManager.hpp"

#include <thread>

namespace Hart {
	ma_device AudioManager::s_Device;
	ma_device_config AudioManager::s_Config;

	void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);

	void AudioManager::Init() {
		HART_ENGINE_LOG("Initializing Audio Manager");

		s_Config = ma_device_config_init(ma_device_type_playback);
		s_Config.dataCallback = dataCallback;
	}

	void AudioManager::Deinit() {
		HART_ENGINE_LOG("Deinitializing Audio Manager");
		ma_device_uninit(&s_Device);
		ma_context_uninit(s_Device.pContext);
	}

	void AudioManager::PlaySound(const std::shared_ptr<Sound>& sound) {
		s_Config.playback.format = sound->decoder.outputFormat;
		s_Config.playback.channels = sound->decoder.outputChannels;
		s_Config.sampleRate = sound->decoder.outputSampleRate;
		s_Config.pUserData = reinterpret_cast<void*>(&sound->decoder);

		ma_result result = ma_device_init(nullptr, &s_Config, &s_Device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);

		result = ma_device_start(&s_Device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);
	}

	void AudioManager::PlayMusic(const std::shared_ptr<Music>& music) {
		StopAllMusic();

		s_Config.playback.format = music->decoder.outputFormat;
		s_Config.playback.channels = music->decoder.outputChannels;
		s_Config.sampleRate = music->decoder.outputSampleRate;
		s_Config.pUserData = reinterpret_cast<void*>(&music->decoder);

		ma_result result = ma_device_init(nullptr, &s_Config, &s_Device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);

		result = ma_device_start(&s_Device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);
	}

	void AudioManager::StopAllMusic() {
		ma_device_stop(&s_Device);
	}

	void dataCallback(ma_device* device, void* output, const void* input, ma_uint32 frameCount) {
		ma_decoder* decoder = reinterpret_cast<ma_decoder*>(device->pUserData);
		HART_ASSERT_NOT_EQUAL(decoder, nullptr);

		/* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
		ma_data_source_read_pcm_frames(decoder, output, frameCount, nullptr);

		(void)input;
	}
}
