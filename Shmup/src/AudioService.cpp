#include "AudioService.h"

SDLAudio::SDLAudio(MIX_Mixer* mix)
{
	if (!mix) mix = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	_Mixer = mix;
};

void SDLAudio::PlaySFX(std::string id)
{
	std::map<std::string, MIX_Audio*>::iterator result = _SFXs.find(id);
	if (result != _SFXs.end())
		MIX_PlayAudio(_Mixer, _SFXs[id]);
};

void SDLAudio::PlayStream(std::string id)
{
	std::map<std::string, MIX_Audio*>::iterator result = _Music.find(id);
	if (result == _Music.end())
		return;

	for (std::vector<MIX_Track*>::iterator i = _Tracks.begin(); i != _Tracks.end(); i++)
		if (MIX_GetTrackAudio(*i) == _Music[id])
		{
			if (MIX_TrackPaused(*i))
				MIX_ResumeTrack(*i);
			else
			{
				SDL_PropertiesID options = SDL_CreateProperties();
				SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
				MIX_PlayTrack(*i, options);
				SDL_DestroyProperties(options);
			}
			return;
		}
	
	MIX_Track* mix = MIX_CreateTrack(_Mixer);
	MIX_SetTrackAudio(mix, _Music[id]);
	SDL_PropertiesID options = SDL_CreateProperties();
	SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
	MIX_PlayTrack(mix, options);
	SDL_DestroyProperties(options);
	
};

void SDLAudio::StopSFX(std::string id)
{
	//	Not needed with SDL_Mixer.
	std::cout << "Did you mean to call this? SFXs are fire-and-forget under SDL_Mixer." << std::endl;
};

void SDLAudio::StopStream(std::string id)
{
	for (std::vector<MIX_Track*>::iterator i = _Tracks.begin(); i != _Tracks.end(); i++)
		if (MIX_GetTrackAudio(*i) == _Music[id])
			MIX_StopTrack(*i,0);
};

void SDLAudio::PauseStream(std::string id)
{
	for (std::vector<MIX_Track*>::iterator i = _Tracks.begin(); i != _Tracks.end(); i++)
		if (MIX_GetTrackAudio(*i) == _Music[id])
			MIX_PauseTrack(*i);
};

bool SDLAudio::StreamPlaying(std::string id)
{
	for (std::vector<MIX_Track*>::iterator i = _Tracks.begin(); i != _Tracks.end(); i++)
		if (MIX_GetTrackAudio(*i) == _Music[id])
			return MIX_TrackPlaying(*i);
	return false;
};

bool SDLAudio::StoreSFX(std::string id, std::string filename)
{
	MIX_Audio* sfx = nullptr;
	sfx = MIX_LoadAudio(_Mixer, filename.c_str(), true);

	if (!sfx) return false;

	std::map<std::string, MIX_Audio*>::iterator result = _SFXs.find(id);
	if (result != _SFXs.end())
		MIX_DestroyAudio(result->second);
	_SFXs[id] = sfx;

	return true;
};

bool SDLAudio::StoreStream(std::string id, std::string filename)
{
	MIX_Audio* music = nullptr;
	music = MIX_LoadAudio(_Mixer, filename.c_str(), true);

	if (!music) return false;

	std::map<std::string, MIX_Audio*>::iterator result = _Music.find(id);
	if (result != _Music.end())
		MIX_DestroyAudio(result->second);
	_Music[id] = music;

	return true;
};

/*
SFMLAudio::SFMLAudio()
{

};

void SFMLAudio::PlaySFX(std::string id)
{
	while (((int)_PlayingSFXs.size() > 0) && (_PlayingSFXs[0].getStatus() == sf::Sound::Stopped))
		_PlayingSFXs.erase(_PlayingSFXs.begin());

	_PlayingSFXs.push_back(sf::Sound(_SFXs[id]));
	_PlayingSFXs.back().play();
};

void SFMLAudio::PlayStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
		{
			it->second.play();
			break;
		}
};

void SFMLAudio::StopSFX(std::string id)
{
	for (std::vector<sf::Sound>::iterator it = _PlayingSFXs.begin(); it != _PlayingSFXs.end(); it++)
		if (it->getBuffer() == &_SFXs[id])
			it->stop();
};

void SFMLAudio::StopStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
		{
			it->second.stop();
			break;
		}
};

void SFMLAudio::PauseStream(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
			it->second.pause();
};

bool SFMLAudio::StreamPlaying(std::string id)
{
	for (std::map<std::string, sf::Music>::iterator it = _Streams.begin(); it != _Streams.end(); it++)
		if (it->first == id)
			return it->second.getStatus() == sf::Sound::Playing;
	return false;
};

bool SFMLAudio::StoreSFX(std::string id, std::string filename)
{
	return _SFXs[id].loadFromFile(filename);
};

bool SFMLAudio::StoreStream(std::string id, std::string filename)
{
	return _Streams[id].openFromFile(filename);
};
*/