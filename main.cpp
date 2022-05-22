/* Copyright (C) 2022 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/software-renderer
 */

#include "tga_image.h"
#include "model.h"
#include "renderer.h"

constexpr static unsigned Width { 1280 };
constexpr static unsigned Height { 720 };

int main() {
    
    // prepare empty img
    tga_image img(Width, Height);
    
    // load desired model
    const model in_model("head.obj");
    
    // draw wires on the img
    renderer::raster(in_model, img);

    // TODO:: flip img?

    // store the result
    img.store("out.tga");
    
    return 0;
}