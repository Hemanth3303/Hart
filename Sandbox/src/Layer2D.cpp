#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Graphics/Colors.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"

#include "Maths/Mat4.hpp"

Layer2D::Layer2D(const std::string& name)
	: Layer(name) {
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO("Attached layer: ", getName());

	Hart::Mat4 C{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	Hart::Vec4 vec4 {1, 2, 3, 4};
	Hart::Vec3 vec3 {1, 2, 3};

	HART_CLIENT_WARNING("Matrix C: ", C);
	HART_CLIENT_WARNING("Vec4: ", vec4);
	HART_CLIENT_WARNING("Vec3: ", vec3);

	HART_CLIENT_WARNING("C x vec4 = ", Hart::Mat4::Multiply(C, vec4));
	HART_CLIENT_WARNING("C x vec3 = ", Hart::Mat4::Multiply(C, vec3));
}

void Layer2D::onDetach() {
	HART_CLIENT_INFO(std::string("Detached layer: ") + getName());
}
void Layer2D::onEvent(Hart::Event& e) {
	Hart::EventDispatcher eventDispatcher(e);

	eventDispatcher.dispatch<Hart::MouseMovedEvent>([this](Hart::MouseMovedEvent& e) {
		m_MousePosition.x = e.getXPosition();
		m_MousePosition.y = e.getYPosition();

		return true;
	});
}

void Layer2D::update(const float deltaTime) {
}

void Layer2D::render() {
}
