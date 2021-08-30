#pragma once
#include <Reborn.h>

int sgn(float val) {
	return (0 <= val) - (val < 0);
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
		mouseWheelHandler = std::bind(&CameraController::onMouseWheel, this, std::placeholders::_1);

		app->eventDispatcher().subscribe(Reborn::MouseButtonPressedEvent::TYPE(), &keyPressHandler);
		app->eventDispatcher().subscribe(Reborn::MouseButtonReleasedEvent::TYPE(), &keyReleasedHandler);
		app->eventDispatcher().subscribe(Reborn::MouseMotionEvent::TYPE(), &mouseMoveHandler);
		app->eventDispatcher().subscribe(Reborn::MouseWheelEvent::TYPE(), &mouseWheelHandler);
	}

	void onTick(
		Reborn::Entity cameraControllerEntity, 
		Reborn::TickComponent& component, 
		double time, 
		double delta
	) {
		auto& camera = Reborn::Application::get()->renderer().getCamera();
		Reborn::Vector3 pos = toSpherical(camera.getPosition());
		pos.x += rRel;
		if (buttonPressed) {
			pos.y -= xRel;
			pos.z -= yRel;
			xRel = yRel = 0;
		}

		//constrains
		pos.x = max(pos.x, 0.01);
		pos.z = pos.z < PI ? max(pos.z, 0.0001) : min(pos.z, PI-0.0001);

		camera.setPosition(fromSpherical(pos));
		rRel = 0;
	}

	//Vector3(r, theta, phi)

	Reborn::Vector3 fromSpherical(Reborn::Vector3 p) {
		p.z = fmod(float(p.z), PI);
		float r = p.x;
		return Reborn::Vector3(
			r * sin(p.z) * sin(p.y),
			r * cos(p.z),
			r * sin(p.z) * cos(p.y)
		);
	}

	Reborn::Vector3 toSpherical(Reborn::Vector3 p) {
		float d = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
		return Reborn::Vector3(
			d,
			sgn(p.x) * acos(p.z / sqrt(p.z * p.z + p.x * p.x)),
			acos(p.y / d)
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

	void onMouseWheel(const Reborn::IEvent& evt) {
		const auto& wheelEvent = static_cast<const Reborn::MouseWheelEvent&>(evt);
		rRel = wheelEvent.scrollY * radiusSpeed;
	}

	void onMouseMove(const Reborn::IEvent& evt) {
		const auto& moveEvent = static_cast<const Reborn::MouseMotionEvent&>(evt);
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
	float rRel = 0;
	float speed = 0.01;
	float radiusSpeed = 1;

	Reborn::Entity cameraControllerEntity;
	Reborn::t_EventHandler keyPressHandler;
	Reborn::t_EventHandler keyReleasedHandler;
	Reborn::t_EventHandler mouseMoveHandler;
	Reborn::t_EventHandler mouseWheelHandler;
};
