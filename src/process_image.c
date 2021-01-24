#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    x = (x < 0) ? 0 : x;
    y = (y < 0) ? 0 : y;
    c = (c < 0) ? 0 : c;

    x = (x >= im.w) ? im.w - 1 : x;
    y = (y >= im.h) ? im.h - 1 : y;
    c = (c >= im.c) ? im.c - 1 : c;
    int index = x + im.w*y + im.w*im.h*c;
    return im.data[index];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if ( x < 0 || x >= im.w || y < 0 || y >= im.h || c < 0 || c >= im.c ) {
        return;
    }
    int index = x + im.w*y +im.w*im.h*c;
    im.data[index] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    int i, j, k;
    for ( i = 0; i < copy.w; i++ ) {
        for ( j = 0; j < copy.h; j++ ) {
            for ( k = 0; k < copy.c; k++ ) {
                float pixel = get_pixel(im, i, j, k);
                set_pixel(copy, i, j, k, pixel);
            }
        }
    }
    free_image(im);
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    int i, j;
    for ( i = 0; i < gray.w; i++ ) {
        for ( j = 0; j < gray.h; j++ ) {
            float red = get_pixel(im, i, j, 0);
            float green = get_pixel(im, i, j, 1);
            float blue = get_pixel(im, i, j, 2);
            float pixel = 0.299 * red + 0.587 * green + .114 * blue;
            set_pixel(gray, i, j, 0, pixel);
        }
    }
    free_image(im);
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
}

void clamp_image(image im)
{
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
