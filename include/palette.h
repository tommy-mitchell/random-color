#ifndef RANDOM_PALETTE
#define RANDOM_PALETTE

#include <tonc_video.h>
#include <tonc_memmap.h>

#define PALETTE_SIZE ( 248 )

typedef struct Palette {
    COLOR colors[PALETTE_SIZE]; // max of 256 colors in palette
    u8 index; // current index
    u8 length; // keeps track of how many colors have been added
} Palette;

inline void Palette_initialize(Palette *palette, COLOR firstColor) {
    palette->colors[0] = firstColor;
    palette->index = 0;
    palette->length = 1;
}

// TRUE if added, FALSE if palette is full
inline BOOL Palette_addColor(Palette *palette, COLOR newColor, BOOL overwrite) {
    if(!overwrite)
    {
        // don't add if full and not overwriting
        if(palette->length == PALETTE_SIZE)
            return FALSE;

        // not full and index is at end
        palette->colors[palette->index] = newColor;
        palette->length++;
    }
    else
    {
        // check if at end
        if(palette->index == palette->length)
            palette->index = 0;

        palette->colors[palette->index] = newColor;
    }

    return TRUE;
}

#endif