#pragma once

#include "../Data/triangle3.h"
#include "../Data/RGB_Material.h"
#include <tuple>
#include <vector>
#include <cstdlib>

std::tuple<std::vector<triangle3>*, int> build_scene(size_t cube_count = 1);