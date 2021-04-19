#pragma once
#ifndef __SCENE_STATE__
#define __SCENE_STATE__
enum SceneState
{
	NO_SCENE = -1,
	START_SCENE,
	STORY_SCENE,
	LEVEL_ONE,
	LEVEL_TWO,
	BOSS_LEVEL,
	PAUSE_SCENE,
	END_SCENE,
	WIN_SCENE,
	NUM_OF_SCENES
};
#endif /* defined (__SCENE_STATE__) */