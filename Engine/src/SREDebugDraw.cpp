#include "Mason/SREDebugDraw.h"
#include "SRE/Shader.hpp"
#include "Mason/Physics.hpp"
#include <iostream>

using namespace Mason;
SREDebugDraw::SREDebugDraw() {

}

void SREDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SRE::Shader::getUnlit()->setDepthTest(false);
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 0; i < vertexCount; i++) {
		auto p1 = vertices[i];
		auto p2 = vertices[(i + 1) % vertexCount];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0) * Physics::instance->phScale, glm::vec3(p2.x, p2.y, 0) * Physics::instance->phScale);
	}
	SRE::Shader::getUnlit()->setDepthTest(true);
}
void SREDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SRE::Shader::getUnlit()->setDepthTest(false);
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 0; i < vertexCount; i++) {
		auto p1 = vertices[i];
		auto p2 = vertices[(i + 1) % vertexCount];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0) * Physics::instance->phScale, glm::vec3(p2.x, p2.y, 0) * Physics::instance->phScale);
	}
	SRE::Shader::getUnlit()->setDepthTest(true);
}
void SREDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

	int segments = 180;
	for (int i = 0; i < segments; i++) {
		float angle1 = i * ((float)360 / (float)segments);
		float angle2 = (i + 1) * ((float)360 / (float)segments);
		auto p1 = glm::vec3(center.x + cos(angle1)*radius, center.y + sin(angle1)*radius, 0);
		auto p2 = glm::vec3(center.x + cos(angle2)*radius, center.y + sin(angle2)*radius, 0);
		SRE::Debug::drawLine(p1 * Physics::instance->phScale, p2 * Physics::instance->phScale);
	}
}
void SREDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
	
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

	int segments = int(radius*M_PI * Physics::instance->phScale);
	for (int i = 0; i < segments; i++) {
		float angle1 = float(i * (2 * M_PI / float(segments)));
		float angle2 = float((i + 1) * (2 * M_PI / float(segments)));
		auto p1 = glm::vec3(center.x + cos(angle1)*radius, center.y + sin(angle1)*radius, 0);
		auto p2 = glm::vec3(center.x + cos(angle2)*radius, center.y + sin(angle2)*radius, 0);
		SRE::Debug::drawLine(p1 * Physics::instance->phScale, p2 * Physics::instance->phScale);
	}
	SRE::Debug::drawLine(glm::vec3(center.x, center.y, 0) * Physics::instance->phScale, glm::vec3(center.x + axis.x * radius, center.y + axis.y * radius, 0) * Physics::instance->phScale);
}
void SREDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0) * Physics::instance->phScale, glm::vec3(p2.x, p2.y, 0) * Physics::instance->phScale);
}
void SREDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {

}
void SREDebugDraw::DrawTransform(const b2Transform& xf) {
}