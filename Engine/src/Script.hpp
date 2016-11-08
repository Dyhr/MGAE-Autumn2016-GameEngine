#pragma once
#include "Transform.h"

class Script : public Component
{
public:
	Script(GameObject* gameObject) :Component(gameObject)
	{
		this->gameobject = std::make_shared<GameObject>(*gameObject);
		this->transform = gameObject->getComponent<Transform>();

		OnAwake();
	}
	~Script()
	{
		OnDestroy();
	}

	std::shared_ptr<GameObject> gameobject;
	std::shared_ptr<Transform> transform;

	virtual void OnAwake() {}
	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnDestroy() {}
	//virtual void OnCollisionEnter() {}
	//virtual void OnCollisionStay() {}
	//virtual void OnCollisionExit() {}
	virtual void OnInput() {}
private:
	bool started = false;
	friend Engine;
};
