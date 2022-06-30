#include "ColorChanger.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ColorChanger);

void ColorChanger::init()
{
	ObjectMeshStaticPtr mesh = checked_ptr_cast<ObjectMeshStatic>(node);
	// get the color zone's material 
	color_zone_mat = mesh->getMaterial(0);
}

void ColorChanger::update()
{
	if (color_zone_mat != nullptr)
	{
		// calculate the interpolation coefficient for this frame
		float k = (Math::sin(Game::getTime() * changeSpeed) + 1) / 2.0f;
		//interpolate between two colors with given coefficient and set it to the first surface's material
		color_zone_mat->setParameterFloat4("emission_color", Math::lerp(vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f), k));
		//interpolate between two values of emission intensity with given coefficient and set it to the first surface's material
		color_zone_mat->setParameterFloat("emission_scale", Math::lerp(1.0f, 4.0f, k));
	}
}