#include "AudioManager.hpp"
#include "AudioManagerData.hpp"

#include <thread>

namespace Hart {
	static std::unique_ptr<AudioManagerData> s_Data;

	void dataCallback(ma_device* device, void* output, const void* input, std::uint32_t frameCount);
	std::uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, std::uint32_t frameCount);

	void AudioManager::Init() {
		HART_ENGINE_LOG("Initializing Audio Manager");

		s_Data = std::make_unique<AudioManagerData>();

		for (std::uint32_t i = 0; i < s_Data->MAX_AUDIO_DECODERS; i++) {
			s_Data->decoders[i] = nullptr;
			s_Data->decodersAtEnd[i] = MA_TRUE;
		}

		s_Data->deviceConfig = ma_device_config_init(ma_device_type_playback);
		s_Data->deviceConfig.playback.format = s_Data->SAMPLE_FORMAT;
		s_Data->deviceConfig.playback.channels = s_Data->CHANNEL_COUNT;
		s_Data->deviceConfig.sampleRate = s_Data->SAMPLE_RATE;
		s_Data->deviceConfig.dataCallback = dataCallback;
		s_Data->deviceConfig.pUserData = nullptr;

		ma_result result = ma_device_init(nullptr, &s_Data->deviceConfig, &s_Data->device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);
		

		result = ma_device_start(&s_Data->device);
		HART_ASSERT_EQUAL(result, MA_SUCCESS);
	}

	void AudioManager::Deinit() {
		HART_ENGINE_LOG("Deinitializing Audio Manager");
		StopAllAudio();
		ma_device_uninit(&s_Data->device);
	}

	void AudioManager::PlaySound(const std::shared_ptr<Sound>& sound) {
		s_Data->decoders[s_Data->decoderIndex] = &sound->decoder;
		s_Data->decodersAtEnd[s_Data->decoderIndex] = MA_FALSE;
		s_Data->decoderIndex++;
	}

	void AudioManager::PlayMusic(const std::shared_ptr<Music>& music) {
		s_Data->decoders[s_Data->decoderIndex] = &music->decoder;
		s_Data->decodersAtEnd[s_Data->decoderIndex] = MA_FALSE;
		s_Data->decoderIndex++;
	}

	void AudioManager::StopAllAudio() {
		ma_device_stop(&s_Data->device);
	}

	bool AudioManager::AreAllDecodersAtEnd() {
		for (std::uint32_t i = 0; i < s_Data->decoderIndex; i++) {
			if (s_Data->decodersAtEnd[i] == MA_FALSE) {
				return false;
			}
		}
		return true;
	}

	void dataCallback(ma_device* device, void* output, const void* input, std::uint32_t frameCount) {
		float* outputF32 = reinterpret_cast<float*>(output);

		HART_ASSERT_EQUAL(s_Data->device.playback.format, s_Data->SAMPLE_FORMAT);

		for (std::uint32_t i = 0; i < s_Data->decoderIndex; i++) {
			if(!s_Data->decodersAtEnd[i]) {
				std::uint32_t framesRead = readAndMixPCMFramesF32(s_Data->decoders[i], outputF32, frameCount);
				if (framesRead < frameCount) {
					s_Data->decodersAtEnd[i] = MA_TRUE;
;				}
			}
		}

		(void)input;
	}

	std::uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, std::uint32_t frameCount) {
		ma_result result;
		std::vector<float> temp;
		temp.resize(4096);
		std::uint32_t tempCapInFrames = temp.size() / s_Data->CHANNEL_COUNT;
		std::uint32_t totalFramesRead = 0;
		
		std::uint64_t framesReadThisIteration;
		while (totalFramesRead < frameCount) {
			std::uint32_t totalFramesRemaining = frameCount - totalFramesRead;
			std::uint32_t framesToReadThisIteration = tempCapInFrames;

			if (framesToReadThisIteration > totalFramesRemaining) {
				framesToReadThisIteration = totalFramesRemaining;
			}

			result = ma_decoder_read_pcm_frames(decoder, temp.data(), framesToReadThisIteration, &framesReadThisIteration);

			if (result != MA_SUCCESS || framesReadThisIteration == 0) {
				break;
			}

			for (std::uint64_t i = 0; i < framesReadThisIteration * s_Data->CHANNEL_COUNT; i++) {
				outputF32[static_cast<std::uint64_t>(totalFramesRead) * s_Data->CHANNEL_COUNT + i] += temp[i];
			}
			totalFramesRead += static_cast<std::uint32_t>(framesReadThisIteration);

			if (static_cast<std::uint32_t>(framesReadThisIteration) < framesToReadThisIteration) {
				break; //EOF
			}
		}
		return totalFramesRead;
	}

}
