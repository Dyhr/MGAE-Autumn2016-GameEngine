#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"

using namespace Mason;

class ANoteController : public Script { 
public:
	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_h) gameObject->getComponent<Audio>()->play();
		}
	}
protected:
	ANoteController(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};