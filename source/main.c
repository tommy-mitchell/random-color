#include <tonc.h>
#include "screen.h"
#include "input_random.h"
#include "start.h"
#include "white.h"
#include "overlay.h"

void setupDisplay(void);

#define SIZE_RECT (20)
bool transitionUp(u32 *y, u32 colorIndex);
bool transitionDown(u32 *y, u32 colorIndex);

OBJ_ATTR obj_buffer[OAM_BUFFER_SIZE];

int main(void)
{
	// initializations to calibrate display
	setupDisplay();

	// initialize interrupt handler and enable the 'VBLANK' interrupt
	irq_init(NULL);
	irq_enable(II_VBLANK);

	//Screen_makeScreen("random", (COLOR) qran(), &lists[0], obj_buffer);
	// need to change creation of UI objects to change spot in buffer

	bool started = false;
	u32 frame = 0, yUp = 0, yDown = SCREEN_HEIGHT;
	s32 moveTriBool = 0;

	Screen random;

	Screen testList;
	Screen_makeScreen("test", CLR_MAROON, &testList, obj_buffer, 3);
	pal_bg_mem[2] = testList.palette.colors[0];
	//Screen_moveScreens((Screen[]) { testList }, 1, SCREEN_HEIGHT*2);
	obj_set_pos(testList.ui.name.obj, 0, -160);
	obj_unhide(testList.ui.name.obj, 4);
	oam_copy(oam_mem, obj_buffer, OAM_BUFFER_SIZE);



	// infinite loop to not return to nothing
	while(true)
	{
		// wait for 'VBLANK' interrupt to vsync
		VBlankIntrWait();

		// game logic

		if(!started)
		{
			key_poll();

			if(key_hit(KEY_START))
			{
				// remove start text
				GRIT_CPY(m4_mem, whiteBitmap);

				// seed the RNG w/ current frame
				sqran(frame);

				// show first screen
				Screen_makeScreen("random", (COLOR) qran(), &random, obj_buffer, 0);
				Screen_onChange(&random);
				pal_bg_mem[PALETTE_INDEX] = random.palette.colors[random.palette.index];

				started = true;
			}
		}
		else if(moveTriBool != 0)
		{
			/*if(testList.ui.name.y == 0)
				move = false;
			else
				Screen_moveScreens((Screen[]) { random, testList }, 2, -20);*/
			
			if(FRAME_COUNT(frame, 10))
			{
				if(moveTriBool == 1 && transitionUp(&yUp, 2))
					moveTriBool = 0;
				else if(moveTriBool == -1 && transitionDown(&yDown, 0))
					moveTriBool = 0;
			}
		}
		else
			moveTriBool = InputRandom_run(&random, frame);

		frame++;
	}
}

void setupDisplay(void)
{
	// set DisplayControl to 'Mode 4' (paletted bitmap) and enable 'background 2'
	REG_DISPCNT  = DCNT_MODE4 | DCNT_BG2;
	// turn on rendering of sprites and enable 1D mapping
	REG_DISPCNT |= DCNT_OBJ   | DCNT_OBJ_1D;

	// initialize text engine
	//tte_init_bmp_default(4);

	// copy start bg
	GRIT_CPY(    m4_mem, startBitmap);
	GRIT_CPY(pal_bg_mem, startPal);

	// copy UI sprites
	GRIT_CPY(&tile_mem[5][0], overlayTiles);
	GRIT_CPY(    pal_obj_mem, overlayPal);

	// initialize oam w/ buffer
	oam_init(obj_buffer, OAM_BUFFER_SIZE);

	/*tte_set_pos(100, 100);
	tte_write("test");
	bmp8_drawg(5);*/
}

bool transitionUp(u32 *y, u32 colorIndex)
{
	// draw black rectangle
	bmp8_rect(0, *y, SCREEN_WIDTH, *y + SIZE_RECT, colorIndex, m4_mem, SCREEN_WIDTH);

	*y += SIZE_RECT;

	if(*y == SCREEN_HEIGHT)
	{
		*y = 0;
		return true;
	}

	return false;
}

bool transitionDown(u32 *y, u32 colorIndex)
{
	// draw black rectangle
	bmp8_rect(0, *y, SCREEN_WIDTH, *y + SIZE_RECT, colorIndex, m4_mem, SCREEN_WIDTH);

	if(*y == 0)
	{
		*y = SCREEN_HEIGHT;
		return true;
	}

	*y -= SIZE_RECT;

	return false;
}