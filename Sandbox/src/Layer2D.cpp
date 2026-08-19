#include "Layer2D.hpp"

Layer2D::Layer2D(const std::string& name)
	: Layer(name) {
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO(std::string("Attached layer: ") + getName());
}

void Layer2D::onDetach() {
	HART_CLIENT_INFO(std::string("Detached layer: ") + getName());
}

void Layer2D::onEvent(Hart::Event& e) {
	HART_CLIENT_INFO(e);
}

void Layer2D::update(const float deltaTime) {
}

void Layer2D::render() {
}
