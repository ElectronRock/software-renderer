/* Copyright (C) 2022 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/software-renderer
 */

#pragma once

#include "tga_image.h"
#include "rmath.h"

class model;

namespace renderer {

    void wireframe(const model& in_model, tga_image& in_image, const tga_image::color& color);

    void raster(const model& in_model, tga_image& in_image);

    void raster_triangle(vector3i p1, vector3i p2, vector3i p3, std::vector<int>& z_buffer, tga_image& in_image,
                         const tga_image::color& in_color);
}