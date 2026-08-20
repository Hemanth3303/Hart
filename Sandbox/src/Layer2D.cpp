#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Graphics/Colors.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"

#include "Maths/Mat4.hpp"

Layer2D::Layer2D(const std::string& name)
	: Layer(name), m_Camera(0.0f, 960.0f, 540.0f, 0.0f), m_MousePosition(0.0f, 0.0f) {
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO("Attached layer: ", getName());

	Hart::Mat4 A{
		6, 4, 3, 2,
		3, 5, 6, 2,
		1, 2, 3, 9,
		3, 7, 8, 0
	};

	Hart::Mat4 I = Hart::Mat4::Identity();

	HART_CLIENT_TRACE("Matrix A: ", A);
	HART_CLIENT_TRACE("Matrix I: ", I);
	HART_CLIENT_TRACE("Matrix A^T: ", Hart::Mat4::Transpose(A));
	HART_CLIENT_TRACE("Matrix I^T: ", Hart::Mat4::Transpose(I));
	HART_CLIENT_TRACE("Matrix Det(A): ", Hart::Mat4::Determinant(A));
	HART_CLIENT_TRACE("Matrix Det(I): ", Hart::Mat4::Determinant(I));
	HART_CLIENT_TRACE("Cofactor(A): ", Hart::Mat4::Cofactor(A));
	HART_CLIENT_TRACE("Cofactor(I): ", Hart::Mat4::Cofactor(I));
	HART_CLIENT_TRACE("Adjoint(A): ", Hart::Mat4::Adjoint(A));
	HART_CLIENT_TRACE("Adjoint(I): ", Hart::Mat4::Adjoint(I));
	HART_CLIENT_TRACE("Inverse(A): ", Hart::Mat4::Inverse(A));
	HART_CLIENT_TRACE("Det(Inverse(A)): ", Hart::Mat4::Determinant(Hart::Mat4::Inverse(A)));
	HART_CLIENT_TRACE("Inverse(I): ", Hart::Mat4::Inverse(I));
	HART_CLIENT_TRACE("A x Inverse(A): ", Hart::Mat4::Multiply(A, Hart::Mat4::Inverse(A)));
	HART_CLIENT_TRACE("Inverse(A) x A): ", Hart::Mat4::Multiply(Hart::Mat4::Inverse(A), A));
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
	// Hart::Renderer2D::BeginScene(m_Camera);

	// Hart::Renderer2D::DrawQuad(m_MousePosition, { 30.0f, 30.0f }, Hart::Blue);

	// Hart::Renderer2D::EndScene();
}
