#include "Mason/AudioManager.hpp"

#include "Mason/Audio.hpp"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace Mason;

AudioManager* AudioManager::instance = nullptr;	

std::map<int, Mix_Chunk*> channelsPlaying;

AudioManager * AudioManager::getInstance()
{
	if (instance) {
	}
	else {
		instance = new AudioManager();
		instance->init();
	}
	return instance;	
}

void channelDone(int channel) {
	std::cout << "Freeing channel: " << channel << std::endl;	
	channelsPlaying[channel] = nullptr;
}

void AudioManager::init(int channels)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_ChannelFinished(channelDone);
	initialized = true;
	//Allocate arbitrary channels for audio. TODO base on something, such as e.g. a multiple of the number of audiocomponents in a scene?
	Mix_AllocateChannels(channels);
	maxChannels = Mix_AllocateChannels(-1);
	std::cout << "AudioManager initialized with " << maxChannels << " channels allocated." << std::endl;
}

AudioManager::AudioManager() {
	
}

AudioManager::~AudioManager() {
	cleanUp();
}

void AudioManager::cleanUp()
{
	for (unsigned int i = 0; i < channelsPlaying.size(); i++) {
		if (channelsPlaying[i]) {
			Mix_FreeChunk(channelsPlaying[i]);
		}
	}
	soundEffectMap.clear();
	musicMap.clear();
	Mix_CloseAudio();
	initialized = false;
}

void AudioManager::step()
{	
	if (!initialized) {
		init();
	}	

	for (int i = 0; i < maxChannels; i++) {
		if (sourcesToBePlayed.empty()) break;
		if (channelsPlaying[i]) continue;
		auto audio = sourcesToBePlayed.front();
		if (audio->type == EFFECT) {
			auto soundEffect = soundEffectMap[audio->path];
			if (soundEffect != nullptr) {
				Mix_PlayChannel(i, soundEffect, 0);				
				sourcesToBePlayed.pop();
				channelsPlaying[i] = soundEffect;
			}
			else {
				std::cout << "Bad Wav: " << audio->path.c_str() << std::endl;
			}
		}
		else if (audio->type == MUSIC) {
			auto music = musicMap[audio->path];
			if (music != nullptr && Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(music, -1);
				sourcesToBePlayed.pop();
			}
			else {
				std::cout << "Bad Wav: " << audio->path.c_str() << std::endl;
			}
		}		
	}
}

void AudioManager::playAudioSource(Audio * audioComponent)
{
	if (audioComponent->type == EFFECT) {
		auto soundEffect = soundEffectMap[audioComponent->path];
		if (soundEffect != nullptr) {
			for (int i = 0; i < maxChannels; i++) {
				if (channelsPlaying[i] == nullptr) {
					Mix_PlayChannel(i, soundEffect, 0);
					channelsPlaying[i] = soundEffect;
					return;
				}
			}
		}
	}
	else if (audioComponent->type == MUSIC) {
		auto music = musicMap[audioComponent->path];
		if (music != NULL && Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(music, -1);	
			return;
		}
	}
	sourcesToBePlayed.push(audioComponent);
}

bool AudioManager::loadAudioSource(Audio * audioComponent)
{
	if (audioComponent->type == EFFECT) {
		if (soundEffectMap[audioComponent->path]) return true;
		auto soundEffect = Mix_LoadWAV(audioComponent->path.c_str());
		if (soundEffect != nullptr) {
			soundEffectMap[audioComponent->path] = soundEffect;
			return true;
		}
		return false;
	}
	else if (audioComponent->type == MUSIC) {
		if (musicMap[audioComponent->path]) return true;
		auto music = Mix_LoadMUS(audioComponent->path.c_str());
		if (music != nullptr) {
			musicMap[audioComponent->path] = music;
			return true;
		}
		return false; 
	}
	return false;
}
