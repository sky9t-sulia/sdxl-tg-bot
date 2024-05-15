#ifndef STATIC_TEXT_H_
#define STATIC_TEXT_H_

#include <Arduino.h>

const String helpMessage = "To generate image type:\n"
                               "/sdxl prompt;negative prompt;style;orientation\n\n"
                               "The negative prompt, style and orientation is optional fields\n\n"
                               "Minimal example: /sdxl a cat\n"
                               "Full example: /sdxl a cat;ugly;anime;portrait\n\n"
                               "List of styles:\n"
                               "'enhance', 'anime', 'photographic', 'digital-art', 'comic-book',"
                               "'fantasy-art', 'analog-film', 'neonpunk', 'isometric', 'lowpoly',"
                               "'origami', 'line-art', 'craft-clay', 'cinematic', '3d-model',"
                               "'pixel-art', 'texture', 'futuristic', 'realism', 'watercolor',"
                               "'photorealistic'\n\nOrientations: 'landscape', 'portrait'";

#endif