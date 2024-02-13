#include "HartPch.hpp"
#include "AudioManager.hpp"
#include "AudioManagerData.hpp"

namespace Hart {
	static std::unique_ptr<AudioManagerData> s_Data;

	void dataCallback(ma_device* device, void* output, const void* input, std::uint32_t frameCount);
	std::uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, std::uint32_t frameCount);

	void AudioManager::Init() {
		HART_ENGINE_LOG("Initializing Audio Manager");

		s_Data = std::make_unique<AudioManagerData>();

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
		for (auto& audioDecoder : s_Data->audioDecoders) {
			delete audioDecoder.decoder;
		}
		s_Data->audioDecoders.clear();
		ma_device_stop(&s_Data->device);
		ma_device_uninit(&s_Data->device);
	}

	void AudioManager::PlaySound(const std::shared_ptr<Sound>& sound) {
		ma_decoder_config config = ma_decoder_config_init(s_Data->SAMPLE_FORMAT, s_Data->CHANNEL_COUNT, s_Data->SAMPLE_RATE);

		ma_decoder* decoder = new ma_decoder;

		std::string filePath = sound->getFilePath();
		ma_result result = ma_decoder_init_file(filePath.c_str(), &config, decoder);
		HART_ASSERT_EQUAL(result, MA_SUCCESS, "failed to create sound decoder");

		ma_data_source_set_looping(decoder, sound->isLooping());
		s_Data->audioDecoders.emplace_back(decoder, MA_FALSE);
	}

	void AudioManager::PlayMusic(const std::shared_ptr<Music>& music) {
		ma_decoder_config config = ma_decoder_config_init(s_Data->SAMPLE_FORMAT, s_Data->CHANNEL_COUNT, s_Data->SAMPLE_RATE);

		ma_decoder* decoder = new ma_decoder;

		std::string filePath = music->getFilePath();
		ma_result result = ma_decoder_init_file(filePath.c_str(), &config, decoder);
		HART_ASSERT_EQUAL(result, MA_SUCCESS, "failed to create music decoder");

		ma_data_source_set_looping(decoder, music->isLooping());
		s_Data->audioDecoders.emplace_back(decoder, MA_FALSE);
	}

	void AudioManager::PuaseAllAudio() {
		ma_device_stop(&s_Data->device);
	}

	void AudioManager::ResumeAlludio() {
		ma_device_start(&s_Data->device);
	}


	bool AudioManager::AreAllDecodersAtEnd() {
		for (auto& audioDecoder: s_Data->audioDecoders) {
			if (audioDecoder.isAtEnd == MA_FALSE) {
				return false;
			}
		}
		return true;
	}

	void AudioManager::ClearDoneDecoders() {
		for (std::size_t i = 0; i < s_Data->audioDecoders.size(); i++) {
			if (s_Data->audioDecoders[i].isAtEnd) {
				delete s_Data->audioDecoders[i].decoder;
				s_Data->audioDecoders.erase(s_Data->audioDecoders.begin() + i);
				break;
			}
		}
	}

	void dataCallback(ma_device* device, void* output, const void* input, std::uint32_t frameCount) {
		float* outputF32 = reinterpret_cast<float*>(output);

		HART_ASSERT_EQUAL(s_Data->device.playback.format, s_Data->SAMPLE_FORMAT);

		for (auto& audioDecoder : s_Data->audioDecoders) {
			if(!audioDecoder.isAtEnd) {
				std::uint32_t framesRead = readAndMixPCMFramesF32(audioDecoder.decoder, outputF32, frameCount);
				if (framesRead < frameCount) {
					audioDecoder.isAtEnd = MA_TRUE;
;				}
			}
		}

		(void)input;
	}

	std::uint32_t readAndMixPCMFramesF32(ma_decoder* decoder, float* outputF32, std::uint32_t frameCount) {
		ma_result result;
		std::vector<float> temp;
		temp.resize(4096);
		ma_uint32 tempCapInFrames = temp.size() / s_Data->CHANNEL_COUNT;
		ma_uint32 totalFramesRead = 0;
		
		ma_uint64 framesReadThisIteration;
		while (totalFramesRead < frameCount) {
			ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
			ma_uint32 framesToReadThisIteration = tempCapInFrames;

			if (framesToReadThisIteration > totalFramesRemaining) {
				framesToReadThisIteration = totalFramesRemaining;
			}

			// this function also checks if ma_data_source_set_looping() was set to true
			result = ma_data_source_read_pcm_frames(decoder, temp.data(), framesToReadThisIteration, &framesReadThisIteration);

			if (result != MA_SUCCESS || framesReadThisIteration == 0) {
				break;
			}

			for (ma_uint64 i = 0; i < framesReadThisIteration * s_Data->CHANNEL_COUNT; i++) {
				outputF32[static_cast<ma_uint64>(totalFramesRead) * s_Data->CHANNEL_COUNT + i] += temp[i];
			}
			totalFramesRead += static_cast<ma_uint32>(framesReadThisIteration);

			if (static_cast<ma_uint32>(framesReadThisIteration) < framesToReadThisIteration) {
				break; //EOF
			}
		}
		return totalFramesRead;
	}

}
