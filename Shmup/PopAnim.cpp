#include "PopAnim.h"

void PopulateAnimations(ImageManager* img)
{
	//	Player Bullet
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

	//	Player Ship
	AnimationFrame p1(0, 0, 48, 27, 0.2f);
	AnimationFrame p2(48, 0, 48, 27, 0.2f);
	AnimationFrame p3(96, 0, 48, 27, 0.2f);
	Animation panim;
	panim._Frames.push_back(p1);
	panim._Frames.push_back(p2);
	panim._Frames.push_back(p3);
	img->AddAnimation("Player_Idle", panim);

	AnimationFrame pd1(0, 27, 48, 27, 0.1f);
	Animation pdanim;
	pdanim._Frames.push_back(pd1);
	pdanim._Frames.push_back(p1);
	img->AddAnimation("Player_Death", pdanim);

	//	Bomb Enemy
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

	AnimationFrame ba1(0, 32, 32, 32, 0.1f);
	AnimationFrame ba2(32, 32, 32, 32, 0.1f);
	AnimationFrame ba3(64, 32, 32, 32, 0.1f);
	Animation baanim;
	baanim._Frames.push_back(ba1);
	baanim._Frames.push_back(ba2);
	baanim._Frames.push_back(ba3);
	img->AddAnimation("BombEnemy_Armed", baanim);

	AnimationFrame bd(96, 0, 32, 32, 0.05f);
	Animation bdanim;
	bdanim._Frames.push_back(bd);
	bdanim._Frames.push_back(ba1);
	img->AddAnimation("BomdEnemy_Death", bdanim);

	//	Drone Enemy 3 x 45px by 31px
	AnimationFrame d1(0, 0, 45, 31, 0.3f);
	AnimationFrame d2(45, 0, 45, 31, 0.3f);
	AnimationFrame d3(90, 0, 45, 31, 0.3f);
	Animation danim;
	danim._Frames.push_back(d1);
	danim._Frames.push_back(d2);
	danim._Frames.push_back(d3);
	danim._Frames.push_back(d2);
	img->AddAnimation("DroneEnemy_Idle", danim);

	//	Spreader Enemy 3 x 46px by 63px
	AnimationFrame s1(0, 0, 46, 63, 0.3f);
	AnimationFrame s2(46, 0, 46, 63, 0.3f);
	AnimationFrame s3(92, 0, 46, 63, 0.3f);
	Animation sanim;
	sanim._Frames.push_back(s1);
	sanim._Frames.push_back(s2);
	sanim._Frames.push_back(s3);
	sanim._Frames.push_back(s2);
	img->AddAnimation("SpreaderEnemy_Idle", sanim);

	//	Tank Enemy 3 x 80px by 58px
	AnimationFrame t1(0, 0, 80, 58, 0.3f);
	AnimationFrame t2(80, 0, 80, 58, 0.3f);
	AnimationFrame t3(160, 0, 80, 58, 0.3f);
	Animation tanim;
	tanim._Frames.push_back(t1);
	tanim._Frames.push_back(t2);
	tanim._Frames.push_back(t3);
	tanim._Frames.push_back(t2);
	img->AddAnimation("TankEnemy_Idle", tanim);

	//	Swarm Enemy 3 x 26px by 31px
	AnimationFrame sw1(0, 0, 26, 31, 0.3f);
	AnimationFrame sw2(26, 0, 26, 31, 0.3f);
	AnimationFrame sw3(52, 0, 26, 31, 0.3f);
	Animation swanim;
	swanim._Frames.push_back(sw1);
	swanim._Frames.push_back(sw2);
	swanim._Frames.push_back(sw3);
	swanim._Frames.push_back(sw2);
	img->AddAnimation("SwarmEnemy_Idle", swanim);

	//	Enemy Bullet
	AnimationFrame eb(0, 0, 16, 16, 0.2f);
	Animation ebanim;
	ebanim._Frames.push_back(eb);
	AnimationFrame eb2(16, 0, 16, 16, 0.2f);
	ebanim._Frames.push_back(eb2);
	AnimationFrame eb3(32, 0, 16, 16, 0.2f);
	ebanim._Frames.push_back(eb3);
	AnimationFrame eb4(48, 0, 16, 16, 0.2f);
	ebanim._Frames.push_back(eb4);
	img->AddAnimation("EBullet_Idle", ebanim);

	//	Explosion
	AnimationFrame ex1(0, 0, 32, 32, 0.1f);
	AnimationFrame ex2(32, 0, 32, 32, 0.1f);
	AnimationFrame ex3(64, 0, 32, 32, 0.1f);
	AnimationFrame ex4(96, 0, 32, 32, 0.1f);
	AnimationFrame ex5(128, 0, 32, 32, 0.1f);
	AnimationFrame ex6(0, 32, 32, 32, 0.1f);
	AnimationFrame ex7(32, 32, 32, 32, 0.1f);
	AnimationFrame ex8(64, 32, 32, 32, 0.1f);
	AnimationFrame ex9(96, 32, 32, 32, 0.1f);
	AnimationFrame ex10(128, 32, 32, 32, 0.1f);
	Animation exanim;
	exanim._Frames.push_back(ex1);
	exanim._Frames.push_back(ex2);
	exanim._Frames.push_back(ex3);
	exanim._Frames.push_back(ex4);
	exanim._Frames.push_back(ex5);
	exanim._Frames.push_back(ex6);
	exanim._Frames.push_back(ex7);
	exanim._Frames.push_back(ex8);
	exanim._Frames.push_back(ex9);
	exanim._Frames.push_back(ex10);
	exanim._Loop = false;
	img->AddAnimation("Explosion", exanim);
};
