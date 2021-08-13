#pragma once
#include <Reborn.h>

int sgn(float val) {
	return (0 < val) - (val < 0);
}

class CameraController {
public:
	CameraController() = default;
	void init(Reborn::Application* app) {
		cameraControllerEntity = app->entityManager().createEntity();
		Reborn::t_tickHandler handler = std::bind(
			&CameraController::onTick,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4
		);
		app->entityManager().addComponent<Reborn::TickComponent>(cameraControllerEntity, handler);

		keyPressHandler = std::bind(&CameraController::onKeyPress, this, std::placeholders::_1);
		keyReleasedHandler = std::bind(&CameraController::onKeyPress, this, std::placeholders::_1);
		mouseMoveHandler= std::bind(&CameraController::onMouseMove, this, std::placeholders::_1);

		app->eventDispatcher().subscribe(Reborn::MouseButtonPressedEvent::TYPE(), &keyPressHandler);
		app->eventDispatcher().subscribe(Reborn::MouseButtonReleasedEvent::TYPE(), &keyReleasedHandler);
		app->eventDispatcher().subscribe(Reborn::MouseMotionEvent::TYPE(), &mouseMoveHandler);
	}

	void onTick(
		Reborn::Entity cameraControllerEntity, 
		Reborn::TickComponent& component, 
		double time, 
		double delta
	) {
		if (buttonPressed) {
			auto& camera = Reborn::Application::get()->renderer().getCamera();
			Reborn::Vector3 pos = toSpherical(camera.getPosition());
			pos.y += yRel;
			pos.z += xRel;
			camera.setPosition(fromSpherical(pos));
		}
		xRel = yRel = 0;
	}

	//Vector3(r, phi, theta)

	Reborn::Vector3 fromSpherical(Reborn::Vector3 p) {
		return Reborn::Vector3(
			p.x * sin(p.y) * cos(p.z),
			p.x * sin(p.y) * sin(p.z),
			p.x * cos(p.y)
		);
	}

	Reborn::Vector3 toSpherical(Reborn::Vector3 p) {
		float d = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
		return Reborn::Vector3(
			d,
			acos(p.z / d),
			sgn(p.y) * acos(p.x / sqrt(p.x * p.x + p.y * p.y))
		);
	}

	void onKeyPress(const Reborn::IEvent& evt) {
		if (evt.GetType() == Reborn::MouseButtonPressedEvent::TYPE()) {
			auto pressEvent = static_cast<const Reborn::MouseButtonPressedEvent&>(evt);
			if (pressEvent.button == controlButton) {
				buttonPressed = true;
			}
		}
		if (evt.GetType() == Reborn::MouseButtonReleasedEvent::TYPE()) {
			auto pressEvent = static_cast<const Reborn::MouseButtonReleasedEvent&>(evt);
			if (pressEvent.button == controlButton) {
				buttonPressed = false;
			}
		}
	}

	void onMouseMove(const Reborn::IEvent& evt) {
		auto moveEvent = static_cast<const Reborn::MouseMotionEvent&>(evt);
		xRel = moveEvent.xRel * speed;
		yRel = moveEvent.yRel * speed;
	}

	~CameraController() {
		Reborn::Application::get()->entityManager().removeEntity(cameraControllerEntity);
		Reborn::Application::get()->eventDispatcher().unsubscribe(Reborn::MouseButtonPressedEvent::TYPE(), &keyPressHandler);
		Reborn::Application::get()->eventDispatcher().unsubscribe(Reborn::MouseButtonReleasedEvent::TYPE(), &keyReleasedHandler);
		Reborn::Application::get()->eventDispatcher().unsubscribe(Reborn::MouseMotionEvent::TYPE(), &mouseMoveHandler);

	}
private:
	Reborn::MouseButtonCode controlButton = Reborn::MouseButtonCode::button_middle;
	bool buttonPressed = false;
	float xRel = 0;
	float yRel = 0;
	float speed = 0.01;

	Reborn::Entity cameraControllerEntity;
	Reborn::t_EventHandler keyPressHandler;
	Reborn::t_EventHandler keyReleasedHandler;
	Reborn::t_EventHandler mouseMoveHandler;
};
