#pragma once
#include "florp/graphics/Texture2D.h"

class Texture3D: florp::graphics::Texture2D {
public:
	struct Texture3dData {
		std::vector<florp::graphics::Texture2dData> arg;
	};
};