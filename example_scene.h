#pragma once

#include "triangle3.h"
#include "RGB_Material.h"
#include <tuple>
#include <vector>
#include <cstdlib>

std::tuple<std::vector<triangle3>*, int> build_scene(size_t cube_count = 1);