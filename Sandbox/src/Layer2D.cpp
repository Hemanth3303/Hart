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

	Hart::Vec3 unit_vec3_i(1.0f, 0.0f, 0.0f);
	Hart::Vec3 unit_vec3_j(0.0f, 1.0f, 0.0f);
	Hart::Vec3 unit_vec3_k = Hart::Vec3::CrossProduct(unit_vec3_i, unit_vec3_j);
	Hart::Mat4 I = Hart::Mat4::Identity();
	Hart::Mat4 A(5.0f);
	Hart::Mat4 B = Hart::Mat4::Multiply(A, I);
	Hart::Mat4 C{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	Hart::Mat4 D{
		2, 3, 5, 7,
		11, 13, 17, 19,
		23, 29, 31, 37,
		41, 43, 47, 53
	};

	Hart::Mat4 E{
		59, 61, 67, 71,
		73, 79, 83, 89,
		97, 101, 103, 107,
		109, 113, 127, 131
	};

	HART_CLIENT_WARNING("unit_vec3_i: ", unit_vec3_i);
	HART_CLIENT_WARNING("unit_vec3_j: ", unit_vec3_j);
	HART_CLIENT_WARNING("i x j = k: ", unit_vec3_k);
	HART_CLIENT_WARNING("identity matrix: ", I);
	HART_CLIENT_WARNING("Matrix A: ", A);
	HART_CLIENT_WARNING("A x I: ", B);
	HART_CLIENT_WARNING("A x A: ", Hart::Mat4::Multiply(A, A));
	HART_CLIENT_WARNING("A x 3: ", Hart::Mat4::ScalarMultiply(A, 3));
	HART_CLIENT_WARNING("Matrix C: ", C);
	HART_CLIENT_WARNING("A x C: ", Hart::Mat4::Multiply(A, C));
	HART_CLIENT_WARNING("C x I: ", Hart::Mat4::Multiply(C, I));
	HART_CLIENT_WARNING("C x 5: ", Hart::Mat4::ScalarMultiply(C, 5));
	HART_CLIENT_WARNING("Matrix D: ", D);
	HART_CLIENT_WARNING("Matrix E: ", E);
	HART_CLIENT_WARNING("D x E: ", Hart::Mat4::Multiply(D, E));
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
