#ifndef PROMPT_EXTRACTOR_H
#define PROMPT_EXTRACTOR_H

#include <Arduino.h>

/**
 * Struct to hold the prompts and their properties.
 */
struct Prompts {
    String prompt; ///< The main prompt for the image.
    String negativePrompt; ///< The negative version of the prompt.
    String style; ///< The style of the prompt (e.g., "photorealistic").
    String orientation; ///< The orientation of the prompt (e.g., "portrait").
};

/**
 * Function to extract prompts and their properties from an input string.
 * @example "/sdxl a cat;ugly;anime;portrait" will extract: prompt="a cat", negativePrompt="ugly", style="anime", orientation="portrait"
 * @param input The input string to extract the prompts from.
 * @param prompts The Prompts struct to hold the extracted prompts.
 */
void extractPrompts(const String &input, Prompts &prompts) {
    // Initialize the default values
    prompts.prompt = "";
    prompts.negativePrompt = "";
    prompts.style = "photorealistic";
    prompts.orientation = "portrait";

    // Find the position of "/sdxl "
    int sdxlPos = input.indexOf("/sdxl ");
    if (sdxlPos == -1) {
        // "/sdxl " not found, return with default values
        return;
    }

    // Start position for the first directive
    int startPos = sdxlPos + 6; // 6 is the length of "/sdxl "

    // Array to hold the extracted directives
    String directives[4];
    int directiveIndex = 0;

    while (startPos < input.length() && directiveIndex < 4) {
        // Find the position of the next semicolon
        int nextDirectivePos = input.indexOf(";", startPos);

        if (nextDirectivePos == -1) {
            // If no semicolon found, extract the rest of the string and break the loop
            directives[directiveIndex] = input.substring(startPos);
            directiveIndex++;
            break;
        }

        // Extract the directive from startPos to before the semicolon
        directives[directiveIndex] = input.substring(startPos, nextDirectivePos);

        // Update start_pos to the character after the semicolon
        startPos = nextDirectivePos + 1;

        // Move to the next directive
        directiveIndex++;
    }

    // Assign the extracted directives to the output parameters
    if (directiveIndex > 0) prompts.prompt = directives[0];
    if (directiveIndex > 1) prompts.negativePrompt = directives[1];
    if (directiveIndex > 2) prompts.style = directives[2];
    if (directiveIndex > 3) prompts.orientation = directives[3];
}

#endif // PROMPT_EXTRACTOR_H