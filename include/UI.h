#ifndef RANDOM_UI
#define RANDOM_UI

#include <tonc_types.h>
#include <tonc_oam.h>

#define OAM_BUFFER_SIZE 128

#define OBJ_PB     0

#define NAME_X     0
#define NAME_Y     0
#define NAME_TID   512

#define NUMBER_X   0
#define NUMBER_Y   144
#define NUMBER_TID 576

#define HEX_X      200
#define HEX_Y      144
#define HEX_TID    544

typedef struct UI_Object {
    OBJ_ATTR *obj;
    s32 x, y;
	u32 tID;
} UI_Object;

typedef struct UI_List {
    UI_Object   name;
    UI_Object number;
    UI_Object    hex;
} UI_List;

void UI_setup(UI_List *list, OBJ_ATTR obj_buffer[], u32 index);

void UI_move(UI_List *list, s32 moveY);

#endif