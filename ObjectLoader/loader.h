#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../Data/triangle3.h"
#include <tuple>


bool simple_loadOBJ(const std::string& filename, std::vector<triangle3>* triangles);