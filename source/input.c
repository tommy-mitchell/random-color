#include "input.h"
#include <tonc_input.h>

/*void Input_run(Screen_List *list, u32 frame)
{
    //key_poll(); already done in main

    Screen *currentScreen = &(list->screens[list->index]);

    if(key_hit(KEY_RIGHT))
    {
        // if already at the end of the palette
        if(currentScreen->palette.index == currentScreen->palette.length - 1)
        {
            // attempt to add a random color -> change later to accomadate lists
           // BOOL added = Palette_addColor(&(currentScreen->palette), qran());
            // true only matters if not random
            // maybe don't let palette care?
        }
    }
}*/