#pragma once
#include <SFML/Audio.hpp>
class CastomMusic : public sf::Music {
public:
	CastomMusic(std::string path) {
		openFromFile(path);
		setLoop(true);
	}
};
class CastomSound : public sf::Sound {
private:
	sf::SoundBuffer buff;
public:
	CastomSound(std::string path) {
		buff.loadFromFile(path);
		setBuffer(buff);
	}
};
CastomMusic menuMusic ("resources\\sounds\\playing bg.wav");
CastomMusic cave      ("resources\\sounds\\cave.wav");

CastomSound walking    ("resources\\sounds\\walking.wav");
CastomSound touchBtn   ("resources\\sounds\\touchBtn.wav");
CastomSound pressedBtn ("resources\\sounds\\pressBtn.wav");
CastomSound screemHeart("resources\\sounds\\heart.wav");

void updateVolume(uint8_t sound, uint8_t music) {
	touchBtn.setVolume(sound);
	pressedBtn.setVolume(sound);
	walking.setVolume(sound);
	screemHeart.setVolume(sound);
	cave.setVolume(sound * 0.2);

	menuMusic.setVolume(music);
}