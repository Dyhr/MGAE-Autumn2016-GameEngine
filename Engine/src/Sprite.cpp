#include "Mason/Sprite.h"

#include <vector>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include <SRE/Texture.hpp>
#include <SRE/Mesh.hpp>

using namespace Mason;

Sprite::Sprite(int x, int y, int width, int height, float anchorX, float anchorY, std::shared_ptr<SRE::Texture> texture) {
	
	this->texture = texture;

	using namespace glm;
	//scale
	width /= this->pixelsperunit;
	height /= this->pixelsperunit;

	float dx = anchorX * width;
	float dy = anchorY * height;
	std::vector<vec3> vertices({
		vec3{ width - dx, -dy, 0 }, vec3{ width - dx, height - dy, 0 }, vec3{ -dx, -dy, 0 },
		vec3{ -dx, -dy, 0 }, vec3{ width - dx, height - dy, 0 }, vec3{ -dx, height - dy, 0 },
	});
	std::vector<vec3> normals;

	float a = float(x) / float(texture->getWidth());
	float b = float(y) / float(texture->getHeight());
	float c = float(width) / float(texture->getWidth()) + a;
	float d = float(height) / float(texture->getHeight()) + b;
	std::vector<vec2> uvs({
		vec2{ c, b }, vec2{ c, d }, vec2{ a, b },
		vec2{ a, b }, vec2{ c, d }, vec2{ a, d }
	});

	this->mesh = std::make_shared<SRE::Mesh>(vertices, normals, uvs);
}

std::shared_ptr<SRE::Texture> Sprite::getTexture() {
	return this->texture;
}
void Sprite::setTexture(std::shared_ptr<SRE::Texture> t) {
	this->texture = t;
}
void Sprite::draw(glm::mat4 matrix) const
{
	SRE::Shader* shader = SRE::Shader::getUnlitSprite();
	shader->set("tex", texture.get());
	SRE::SimpleRenderEngine::instance->draw(mesh.get(), matrix, shader);
}
