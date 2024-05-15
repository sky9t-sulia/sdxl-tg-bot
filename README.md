Telegram bot for generating Stable Diffusion images by sending text prompts.
It uses https://monsterapi.ai to work. They provide 2500 free tokens. Each image costs 2 tokens.

Works on ESP32. Tested on ESP32C3

## Usage
The prompt is:
- ``/sdxl <prompt>;<negative prompt?>;<style?>;<orientation?>`` (negative prompt, style, and orientation are optional)
- ``/help`` to get help

## Example

- ``/sdxl a cat sitting on sofa;ugly, deformed;photorealistic;landscape``

## Extra
Styles:\
``'enhance', 'anime', 'photographic', 'digital-art', 'comic-book','fantasy-art', 'analog-film', 'neonpunk', 'isometric', 'lowpoly','origami', 'line-art', 'craft-clay', 'cinematic', '3d-model', 'pixel-art', 'texture', 'futuristic', 'realism', 'watercolor', 'photorealistic'`` (default ``photorealistic``)

Orientation:\
``landscape, portrait`` (default ``portrait``)
