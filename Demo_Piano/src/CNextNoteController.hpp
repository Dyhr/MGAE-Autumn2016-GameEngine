#pragma once

#include "Mason/Script.hpp"
#include "Mason/GameObject.hpp"
#include "Mason/Audio.hpp"

using namespace Mason;

class CNextNoteController : public Script {
public:
	static Script* Create(GameObject* gameObject)
	{
		return new CNextNoteController(gameObject);
	}
	void OnUpdate() override {

	}
	void OnInput(SDL_Event event) override {
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_k) gameObject->getComponent<Audio>()->play();
		}
	}
protected:
	CNextNoteController(GameObject* gameObject) : Script(gameObject)
	{
	}
	friend GameObject;
private:
};