#include <cairo.h>

#include <iostream>

int main()
{
    constexpr int width = 640;
    constexpr int height = 420;
    const char* outputPath = "cairo_test.png";

    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 0.05, 0.07, 0.10);
    cairo_rectangle(cr, 40.0, 40.0, 560.0, 340.0);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.12, 0.42, 0.84);
    cairo_rectangle(cr, 90.0, 90.0, 180.0, 110.0);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0.10, 0.62, 0.28);
    cairo_arc(cr, 410.0, 145.0, 62.0, 0.0, 6.283185307179586);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0.86, 0.18, 0.14);
    cairo_set_line_width(cr, 8.0);
    cairo_move_to(cr, 115.0, 285.0);
    cairo_line_to(cr, 255.0, 245.0);
    cairo_line_to(cr, 395.0, 305.0);
    cairo_line_to(cr, 535.0, 235.0);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.05, 0.07, 0.10);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24.0);
    cairo_move_to(cr, 90.0, 355.0);
    cairo_show_text(cr, "Cairo render test");

    cairo_status_t status = cairo_surface_write_to_png(surface, outputPath);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    if (status != CAIRO_STATUS_SUCCESS)
    {
        std::cerr << "Failed to write PNG: " << cairo_status_to_string(status) << std::endl;
        return 1;
    }

    std::cout << "Generated " << outputPath << std::endl;
    return 0;
}
