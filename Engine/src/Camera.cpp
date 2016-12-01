#include <Mason/Camera.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <iostream>
#include "Mason/Config.hpp"


using namespace Mason;

Camera::Camera(GameObject* gameObject) : Transform(gameObject)
{
	cam = new SRE::Camera();
}

void Camera::transformize()
{
	Transform::transformize();
	cam->setWindowCoordinates(*Config::getInt("window-width") * (viewportMax.x - viewportMin.x), *Config::getInt("window-height") * (viewportMax.y - viewportMin.y));

	cam->setViewTransform(matrix);
}

void Camera::setScale(glm::vec3 scale)
{
	Transform::setScale(glm::vec3(1 / scale.x, 1 / scale.y, 1 / scale.z));
}

void Camera::setPosition(glm::vec3 position)
{
	Transform::setPosition(-position + glm::vec3(*Config::getInt("window-width")/2, *Config::getInt("window-height")/2,0));
}

glm::vec3 Camera::getScale()
{
	return glm::vec3(1 / scale.x, 1 / scale.y, 1 / scale.z);
}

glm::vec3 Camera::getPosition()
{
	return -position + glm::vec3(*Config::getInt("window-width") / 2, *Config::getInt("window-height") / 2, 0);
}

glm::vec2 Camera::getViewportMin() const
{
	return viewportMin;
}

void Camera::setViewportMin(glm::vec2 viewport_min)
{
	viewportMin = viewport_min;
	cam->setViewport(viewportMin.x * *Config::getInt("window-width"), 
					 viewportMin.y * *Config::getInt("window-height"),
					 (viewportMax.x - viewportMin.x) * *Config::getInt("window-width"),
					 (viewportMax.y - viewportMin.y) * *Config::getInt("window-height"));
	transformize();
}

glm::vec2 Camera::getViewportMax() const
{
	return viewportMax;
}

void Camera::setViewportMax(glm::vec2 viewport_max)
{
	viewportMax = viewport_max;
	cam->setViewport(viewportMin.x * *Config::getInt("window-width"),
					 viewportMin.y * *Config::getInt("window-height"),
					 (viewportMax.x - viewportMin.x) * *Config::getInt("window-width"),
					 (viewportMax.y - viewportMin.y) * *Config::getInt("window-height"));
	transformize();
}

Camera::~Camera()
{
	delete cam;
}
