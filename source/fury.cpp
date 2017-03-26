/*
 * fury.cpp
 *
 *  Created on: Mar 23, 2017
 *      Author: efarhan
 */

#include <fury.h>


static int furyAnimFrames[] = {1,4,4};
static int furyAnimOffset[] = {0,1,5};

void initFury(Fury *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

	sprite->frame_gfx = (u8*)gfx;

	dmaCopy(furySpritePal, SPRITE_PALETTE, 512);
}

void animateFury(Fury *sprite)
{
	int currentFrame = sprite->anim_frame/FURY_FRAMES_PER_ANIM;
	if(currentFrame == furyAnimFrames[sprite->state])
	{
		sprite->anim_frame = 0;
		currentFrame = 0;
	}
	int frame = furyAnimOffset[sprite->state]+currentFrame;

	u8* offset = sprite->frame_gfx + frame * 64*64;

	dmaCopy(offset, sprite->sprite_gfx_mem, 64*64);
}

void showFury(Fury *sprite)
{
	int posX = sprite->x;
	if(sprite->hFlip)
		posX-=64-48;
	oamSet(&oamMain, 0, posX, sprite->y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color,
				sprite->sprite_gfx_mem, -1, false, false, sprite->hFlip, false, false);
}