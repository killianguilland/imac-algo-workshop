#include <sil/sil.hpp>
#include <random.hpp>
#include <image-utils.hpp>
#include <iostream>

void eye(sil::Image& image, glm::vec2 center) {
    circle(image, center, 25, 5, 0.0f, 0.0f, 0.0f);
    circle(image, center, 20, 20, 1.0f, 1.0f, 1.0f);
    center.x += random_int(-6, 6);
    center.y -= random_int(-6, 6);
    circle(image, center, 5, 5, 0.0f, 0.0f, 0.0f);
}

void pngs_to_gif(const std::string prefix = "") {
    std::string command = "convert -delay 10 -loop 0 ../output/" + prefix + "*.png ../output.gif";
    system(command.c_str());
}

int main() // Circle
{
    sil::Image image {500/*width*/, 1000/*height*/};
    glm::vec2 center ;
    rectangle(image, {0, 0}, 500, 1000, 0.96f, 0.5f, 1.0f);
    rectangle(image, {250, 500}, 100, 450, 0.25f, 0.25f, 0.25f);
    rectangle(image, {100, 900}, 50, 50, 0.25f, 0.25f, 0.25f);
    rectangle(image, {400, 900}, 50, 50, 0.25f, 0.25f, 0.25f);
    eye(image, {200, 860});
    eye(image, {300, 860});
    circle(image, {250, 50}, 20, 20, 0.0f, 0.0f, 0.0f);
    rectangle(image, {250, 65}, 20, 10, 0.0f, 0.0f, 0.0f);
    image.save("output/11.png");

    // sil::Image image {500/*width*/, 1000/*height*/};

    // for (int i = 0; i < 9; i++)
    // {
    //     sil::Image image {500/*width*/, 500/*height*/};
    //     circle(image, {(image.width() / 9) * i, 250}, 20, 20, 1.0f, 1.0f, 1.0f);
    //     image.save("output/anim-" + std::to_string(i) + ".png");
    // }

    // pngs_to_gif("anim-");

    // sil::Image image {500/*width*/, 500/*height*/};
    // circle(image, {250, 250}, 200, 10, 1.0f, 1.0f, 1.0f);
    // for (int i = 0; i < 6; i++)
    // {
    //     /* code */
    //     circle(image, {250, 250}, 200 - i * 30, 10, 1.0f, 1.0f, 1.0f);
    // }
    
    // image.save("output/13.png");

    // sil::Image image {500/*width*/, 500/*height*/};
    // rosace(image, 12);
    // image.save("output/14.png");

    // sil::Image image{"images/harvey.png"};
    // mosaic(image, 4);
    // image.save("output/15.5.png");

    // sil::Image image{"images/logo.png"};
    // glitch(image);
    // image.save("output/16.png");

    // sil::Image image{500/*width*/, 500/*height*/};
    // // mandelbrot(image);
    // gradient(image);
    // image.save("output/5.png");

    // sil::Image image{"images/photo_faible_contraste.jpg"};
    // histogram_normalization(image);
    // image.save("output/histogram.png");

    // sil::Image image{500, 500};
    // circle(image, {250, 250}, 200, 200, 1.0f, 1.0f, 1.0f);
    // image.save("output/disk.png");

    // sil::Image image {1025/*width*/, 1025/*height*/};
    // diamond_square(image, 1.0f);
    // image.save("output/19.png");

    return 0;
}



