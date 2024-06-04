#pragma once

struct RGB_Material 
{
	public:
		color3 _ambiente;
		color3 _diffuse;
		color3 _specular;
		double _shinyness;

		RGB_Material() = default;

		RGB_Material(const color3& _ambiente, const color3& _diffuse, const color3& _specular, double _shinyness)
			: _ambiente(_ambiente), _diffuse(_diffuse), _specular(_specular), _shinyness(_shinyness)
		{
		}
};