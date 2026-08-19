#pragma once

#include "Core/Layer.hpp"

class Layer2D : public Hart::Layer {
public:
	Layer2D(const std::string& name);
	~Layer2D();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Hart::Event& e) override;
	virtual void update(const float deltaTime) override;
	virtual void render() override;
private:
};
