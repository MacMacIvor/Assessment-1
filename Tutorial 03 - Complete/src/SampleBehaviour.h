#pragma once
#include "florp/game/IBehaviour.h"
#include "Logging.h"
#include "florp/game/Transform.h"
#include "florp/game/SceneManager.h"
#include "florp/app/Timing.h"
#include "imgui.h"
#include "florp/game/RenderableComponent.h"

class SampleBehaviour : public florp::game::IBehaviour {
public:
	SampleBehaviour(const glm::vec3& speed) : IBehaviour(), mySpeed(speed) {};
	virtual ~SampleBehaviour() = default;

	virtual void Update(entt::entity entity) override {
		auto& transform = CurrentRegistry().get<florp::game::Transform>(entity);
		transform.Rotate(mySpeed * florp::app::Timing::DeltaTime);
	}

private:
	glm::vec3 mySpeed;
};


class MovingBehaviour : public florp::game::IBehaviour {
public:
	MovingBehaviour(const glm::vec3& speed) : IBehaviour(), mySpeed(speed) {};
	virtual ~MovingBehaviour() = default;

	virtual void Update(entt::entity entity) override {
		auto& transform = CurrentRegistry().get<florp::game::Transform>(entity);
		transform.SetPosition(transform.GetLocalPosition() + mySpeed * florp::app::Timing::DeltaTime * sin(totTime));
		totTime += florp::app::Timing::DeltaTime / 4;
	}
	//myLocalPosition += displacement;
private:
	glm::vec3 mySpeed;
	float totTime = 0;
};



class RotateAround : public florp::game::IBehaviour {
public:
	RotateAround(const glm::vec3& pivoT, const glm::vec3& initAngle, const glm::vec3& speed, const float disT, const int axiS /*once completed 1 = x, 2 = y, 3 = z*/) : IBehaviour(), mySpeed(speed), angleTrack(initAngle), pivot(pivoT), dist(disT), totTime(0), axis(axiS) {};
	virtual ~RotateAround() = default;

	virtual void Update(entt::entity entity) override {
		auto& transform = CurrentRegistry().get<florp::game::Transform>(entity);
		//transform.Rotate(mySpeed * florp::app::Timing::DeltaTime);
		//transform.RotateAroundPivot(pivot, startAngle, angleTrack * florp::app::Timing::DeltaTime, dist, axis);
		switch (axis) {
		case 2:
			transform.SetPosition({ pivot.x + dist * cos(angleTrack.x), 
									transform.GetLocalPosition().y,
									pivot.z + dist * sin(angleTrack.z) }); //Technically should probably be -sin but it still works

		}
		angleTrack += mySpeed * florp::app::Timing::DeltaTime;
	}

private:
	glm::vec3 mySpeed;
	glm::vec3 angleTrack;
	glm::vec3 pivot;
	const float dist;
	const int axis;
	float totTime = 0;
};
