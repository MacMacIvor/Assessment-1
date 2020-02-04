#pragma once
#include "florp/app/ApplicationLayer.h"
#include "florp/game/SceneManager.h"
#include "florp/game/RenderableComponent.h"
#include <florp\graphics\MeshData.h>
#include <florp\graphics\MeshBuilder.h>
#include <florp\graphics\ObjLoader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <florp\game\Transform.h>
#include "SampleBehaviour.h"
#include "CameraComponent.h"
#include "florp/app/Application.h"

class SceneBuilder : public florp::app::ApplicationLayer {
public:
	void Initialize() override;	
};