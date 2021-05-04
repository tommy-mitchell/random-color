#include <tonc_input.h>
#include "input_random.h"

void handleRight(Palette *palette);

s32 InputRandom_run(Screen *random, u32 frame)
{
    key_poll();

    if(key_hit(KEY_UP))
        return  1;
    if(key_hit(KEY_DOWN))
        return -1;

    Palette *palette = &(random->palette);

    if(key_held(KEY_RIGHT))
    {
        if(FRAME_COUNT(frame, 40))
        {
            handleRight(palette);
            Screen_onChange(random);
        }

        return 0;
    }

    if(key_hit(KEY_RIGHT) )//|| ( key_held(KEY_RIGHT) && FRAME_COUNT(frame, 15) ))
    {
        handleRight(palette);
        Screen_onChange(random);
    }
    else if(key_hit(KEY_LEFT) && palette->length > 1) // only move left if not at beginning
    {
        // going back and then forward once list is filled causes overwrites at current location,
        //     not only when wrapping around

        if(palette->index == 0)
            palette->index = palette->length - 1; // move to end
        else
            palette->index--;

        Screen_onChange(random);
    }

    // toggle UI
    if(key_hit(KEY_START))
        REG_DISPCNT ^= DCNT_OBJ;


    return 0;
}

void handleRight(Palette *palette)
{
    // index++
    // check if full (length==size) -> addColor(overwrite = true)
    //     if at end -> wrap around (have addColor deal with that)
    // otherwise if at end (index==length) -> addColor(overwrite = false)

    palette->index++;

    // palette full -> overwrite
    if(palette->length == PALETTE_SIZE)
    {
        Palette_addColor(palette, qran(), TRUE);
        //BG_PALETTE_LOCATION[palette->index] = palette->colors[palette->index];
        pal_bg_mem[PALETTE_INDEX + palette->index] = palette->colors[palette->index];
    }
    else if(palette->index == palette->length) // at end of palette, add new color
    {
        Palette_addColor(palette, qran(), FALSE);
        //BG_PALETTE_LOCATION[palette->index] = palette->colors[palette->index];
        pal_bg_mem[PALETTE_INDEX + palette->index] = palette->colors[palette->index];
    }
}