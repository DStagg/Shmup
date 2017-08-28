#include "PopAnim.h"

void PopulateAnimations(ImageManager* img)
{
	AnimationFrame f(0, 0, 16, 16, 0.2f);
	Animation anim;
	anim._Frames.push_back(f);
	AnimationFrame f2(16, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f2);
	AnimationFrame f3(32, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f3);
	AnimationFrame f4(48, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f4);
	img->AddAnimation("PBullet_Idle", anim);

	AnimationFrame p1(0, 0, 48, 27, 0.2f);
	AnimationFrame p2(48, 0, 48, 27, 0.2f);
	AnimationFrame p3(96, 0, 48, 27, 0.2f);
	Animation panim;
	panim._Frames.push_back(p1);
	panim._Frames.push_back(p2);
	panim._Frames.push_back(p3);
	img->AddAnimation("Player_Idle", panim);

	AnimationFrame e1(0, 0, 32, 32, 0.3f);
	AnimationFrame e2(32, 0, 32, 32, 0.3f);
	AnimationFrame e3(64, 0, 32, 32, 0.3f);
	Animation eanim;
	eanim._Frames.push_back(e1);
	eanim._Frames.push_back(e2);
	eanim._Frames.push_back(e3);
	eanim._Frames.push_back(e3);
	eanim._Frames.push_back(e2);
	eanim._Frames.push_back(e1);
	img->AddAnimation("BombEnemy_Idle", eanim);








};
