/*
    contains all of the data for individual 'screens'

    * each 'screen' represents a palette list (e.g. "random", "list 1", "pal2", etc)

    * stores:
        - a 'UI_List' object with each sprite for the respective list
        - a 'Palette' object that stores the colors of the list

    * API:
        - Screen_MakeScreen(name, first COLOR) -> makes UI_List and Palette
        - Screen_SwapToScreen(direction, *currentScreen, *nextScreen)
            & enables next screen
            & does transition
            & disables previous screen
        - Screen_ToggleUI(*screen)

*/

#ifndef RANDOM_SCREEN
#define RANDOM_SCREEN

#include <tonc_video.h>
#include <tonc_types.h>
#include <tonc_tte.h>
#include "posprintf.h"
#include "UI.h"
#include "palette.h"

#define BG_COLOR_INDEX ( 0 )
#define PALETTE_INDEX ( 8 )
//#define BG_PALETTE_LOCATION ( (COLOR*) 0x0500000F ) //( ( pal_bg_mem ) + ( ( ( PAL_BG_SIZE ) / 2 ) - ( PALETTE_SIZE ) ) )

#define SCREEN_MOVE_Y ( 60 )

typedef struct Screen {
    UI_List ui;
    Palette palette;
    char*   name; // need to set limit
} Screen;

/*typedef struct Screen_List {
    Screen screens[5]; // 5 for now
    u8 index;
    // dynamic: 256 COLORs (u16), u8 index, name (8-10 chars? u8), list:
										// 3x (3 u32, 4 u16)
										// -> 4648 bits?
										// sizeof(Screen) ?
} Screen_List;*/

inline void Screen_onChange(Screen *screen);

inline void Screen_makeScreen(char* name, COLOR firstColor, Screen *newScreen, OBJ_ATTR obj_buffer[], u32 index) {
    newScreen->name = name;
    UI_setup(&newScreen->ui, obj_buffer, index);
    Palette_initialize(&newScreen->palette, firstColor);

    //Screen_onChange(newScreen);
}

static inline void Screen_moveScreens(Screen screens[], u32 length, s32 moveY) {
    // move all UI objs in direction
    for(int index = 0; index < length; index++)
        UI_move(&screens[index].ui, moveY);
}

inline void Screen_onChange(Screen *screen) { // displays new info

   // memcpy16(pal_bg_mem, screen->palette.colors, PALETTE_SIZE);

    // display current color
	pal_bg_mem[BG_COLOR_INDEX] = screen->palette.colors[screen->palette.index];

   /* tte_set_pos(NAME_X, NAME_Y);
	tte_write(screen->name);

    tte_set_pos(NUMBER_X, NUMBER_Y);
    char number[4]; // 1-256, null terminator
    posprintf(number, "%d", screen->palette.index + 1);
	tte_write(number);

    tte_set_pos(HEX_X, HEX_Y);
    char hex[32]; // should be 7 (6 digits, NT)
    posprintf(hex, "%d", screen->palette.colors[screen->palette.index]);
	tte_write(hex);*/
}

#endif