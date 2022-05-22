#include "renderer.h"
#include "model.h"
#include "line.h"
#include "rmath.h"

namespace renderer {

    void convert_draw(vector3f p1, vector3f p2, tga_image& in_image, const tga_image::color& in_color) {
        p1.x = (p1.x + 1) * in_image.size().first / 2;
        p1.y = (1 - p1.y ) * in_image.size().second / 2;
        p2.x = (p2.x + 1) * in_image.size().first / 2;
        p2.y = (1 - p2.y) * in_image.size().second / 2;
        line::brezenhaim({(int)p1.x, (int)p1.y}, {(int)p2.x, (int)p2.y}, [&](int x, int y){in_image.set(x, y, in_color);});
    }

    void wireframe(const model& in_model, tga_image& in_image, const tga_image::color& in_color) {
        auto&& vertices = in_model.get_vert();
        for(auto&& [p0, p1, p2] : in_model.get_trian()) {
            convert_draw(vertices[p0], vertices[p1], in_image, in_color);
            convert_draw(vertices[p1], vertices[p2], in_image, in_color);
            convert_draw(vertices[p2], vertices[p0], in_image, in_color);
        }
    }

    void raster_triangle(vector3f p1, vector3f p2, vector3f p3, 
        std::vector<int>& z_buffer,  tga_image& in_image, const tga_image::color& in_color) {

    }

    void raster(const model& in_model, tga_image& in_image) {
        // create z buffer
        std::vector z_buffer(in_image.size().first * in_image.size().second, std::numeric_limits<int>::min());
        auto&& vertices = in_model.get_vert();

        for(auto&& [p0, p1, p2] : in_model.get_trian()) {

            // TODO: compute intencity
            const auto intencity = 1.0;

            tga_image::color color{ uint8_t(intencity * 255), uint8_t(intencity * 255), 
                uint8_t(intencity * 255), uint8_t(intencity * 255) };

            raster_triangle(vertices[p0], vertices[p1], vertices[p2], 
                z_buffer, in_image, color);
        }
    }

}