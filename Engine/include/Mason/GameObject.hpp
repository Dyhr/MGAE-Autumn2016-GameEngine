#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Transform.h"


namespace Mason {

	class Scene;
	class Script;

	class GameObject {
	public:
		~GameObject();
		GameObject(std::string name);

		std::string getName() const;
		void setName(std::string nm);

		template<typename C>
		std::shared_ptr<C> addComponent();

		bool removeComponent(std::shared_ptr<Component> ptr);

		std::shared_ptr<Script> addScript(std::string name);

		template<typename C>
		std::shared_ptr<C> getComponent();
		template<typename C>
		std::vector<std::shared_ptr<C>> getComponents();

		std::shared_ptr<Transform> getTransform() const;
		void setTransform(std::shared_ptr<Transform>);

	private:
		std::vector<std::shared_ptr<Component>> components;

		std::shared_ptr<Transform> transform;
		std::string name;
		friend class Scene;
	};

	// function templates has to defined in header files
	template<typename C>
	std::shared_ptr<C> GameObject::addComponent() {
		C * c = new C(std::shared_ptr<GameObject>(this));
		auto res = std::shared_ptr<C>(c);
		components.push_back(res);
		return res;
	}

	template<typename C>
	std::shared_ptr<C> GameObject::getComponent() {
		for (auto c : components) {
			auto castPtr = std::dynamic_pointer_cast<C>(c);
			if (castPtr != nullptr)
				return castPtr;
		}
		// not found
		return nullptr;
	}
	template<typename C>
	std::vector<std::shared_ptr<C>> GameObject::getComponents() {
		std::vector<std::shared_ptr<C>> result;
		for (auto c : components) {
			auto castPtr = std::dynamic_pointer_cast<C>(c);
			if (castPtr != nullptr)
				result.push_back(castPtr);
		}
		return result;
	}
}
