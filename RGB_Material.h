#pragma once

struct RGB_Material 
{
	public:

		RGB_Material() = default;

		color3 _object_color;
		double _ambiente;
		double _diffuse;
		double _specular;
		double _shinyness;



		RGB_Material(const color3 object_color, const double ambiente, const double diffuse,
			const double specular, const double shinyness) : _object_color(object_color),
			_ambiente(ambiente), _diffuse(diffuse), _specular(specular), _shinyness(shinyness) {}
};