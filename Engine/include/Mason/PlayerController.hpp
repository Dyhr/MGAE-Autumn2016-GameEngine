#pragma once
#include "Script.hpp"

using namespace Mason;

class PlayerController :public Script
{
protected:
	PlayerController(GameObject* gameObject) : Script(gameObject)
	{
	}

	friend GameObject;

public:
	void OnUpdate() override
	{
		direction = rightDown - leftDown;

		auto pos = transform->getPosition();
		pos.x += direction * speed * Time::getDeltaTime();
		transform->setPosition(pos);

		auto rot = transform->getRotation();
		rot.y += speed * Time::getDeltaTime();
		transform->setRotation(rot);
	}

	void OnInput(SDL_Event event) override
	{
		if(event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a) leftDown = 1;
			if (event.key.keysym.sym == SDLK_d) rightDown = 1;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a) leftDown = 0;
			if (event.key.keysym.sym == SDLK_d) rightDown = 0;
		}
	}

	int leftDown = 0;
	int rightDown = 0;
	int direction = 0;
	float speed = 2.0f;
};