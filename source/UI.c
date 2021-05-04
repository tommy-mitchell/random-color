#include "UI.h"

void loadSprites(UI_Object *name, UI_Object *number, UI_Object *hex, OBJ_ATTR obj_buffer[], u32 index);
void setupUIObject(UI_Object *object);

void UI_setup(UI_List *list, OBJ_ATTR obj_buffer[], u32 index)
{
    loadSprites(&list->name, &list->number, &list->hex, obj_buffer, index);

    setupUIObject(&list->name);
    setupUIObject(&list->number);
    setupUIObject(&list->hex);

    // copy buffer to OAM -> won't overwrite bc there will never be that many
    oam_copy(oam_mem, obj_buffer, OAM_BUFFER_SIZE);
    
}

void loadSprites(UI_Object *name, UI_Object *number, UI_Object *hex, OBJ_ATTR obj_buffer[], u32 index)
{
    *name   = (UI_Object) { 
        .obj = &obj_buffer[(0 + index)],
        .x =   NAME_X, .y =   NAME_Y, .tID =   NAME_TID
    };

    *number = (UI_Object) { 
        .obj = &obj_buffer[(1 + index)],
        .x = NUMBER_X, .y = NUMBER_Y, .tID = NUMBER_TID
    };

    *hex    = (UI_Object) { 
        .obj = &obj_buffer[(2 + index)],
        .x =    HEX_X, .y =    HEX_Y, .tID =    HEX_TID
    };
}

void setupUIObject(UI_Object *object)
{
	obj_set_attr(object->obj, ATTR0_WIDE, ATTR1_SIZE_64x32, ATTR2_PALBANK(OBJ_PB) | object->tID);
	obj_set_pos(object->obj, object->x, object->y);
    obj_hide(object->obj);
}

void UI_move(UI_List *list, s32 moveY)
{
    list->name.y   += moveY;
    list->number.y += moveY;
    list->hex.y    += moveY;

    obj_set_pos(list->name.obj,   list->name.x,   list->name.y);
    obj_set_pos(list->number.obj, list->number.x, list->number.y);
    obj_set_pos(list->hex.obj,    list->hex.x,    list->hex.y);
}