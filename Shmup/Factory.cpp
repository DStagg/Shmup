#include "Factory.h"
#include "Level.h"

EntFactory::EntFactory()
{

};

void EntFactory::Init(Level* lvl, ImageManager* img, sf::RenderWindow* rw)
{
	_Level = lvl;
	_ImgMan = img;
	_Window = rw;
};

Entity* EntFactory::Spawn(int type, float x, float y)
{
	Entity* ent;
	BasicEnt* ta;
	BasicEnt* tb;

	switch (type)
	{
	case Types::Player:
		ent = new PlayerEnt(_Level, _Window);
		ent->GetStats().SetMaxHP(5);
		ent->GetStats().SetHP(5);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Player")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("Player_Idle"));
		ent->GetGraphic().AddAnimation("Death", _ImgMan->GetAnimation("Player_Death"));
		ent->GetGraphic().Swap("Idle");
		break;
	case Types::PlayerBullet:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("PBullet")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("PBullet_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(-300.f);
		break;
	case Types::BombEnemy:
		ent = new BombEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("BombEnemy")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("BombEnemy_Idle"));
		ent->GetGraphic().AddAnimation("Armed", _ImgMan->GetAnimation("BombEnemy_Armed"));
		ent->GetGraphic().AddAnimation("Death", _ImgMan->GetAnimation("BombEnemy_Death"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(125.f);
		break;
	case Types::DroneEnemy:
		ent = new DroneEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("DroneEnemy")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("DroneEnemy_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(100.f);
		ent->GetStats().SetHP(2);
		break;
	case Types::SpreaderEnemy:
		ent = new SpreaderEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("SpreaderEnemy")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("SpreaderEnemy_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(100.f);
		ent->GetStats().SetHP(2);
		break;
	case Types::SwarmEnemy:
		ent = new SwarmEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("SwarmEnemy")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("SwarmEnemy_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(150.f);
		break;
	case Types::TankEnemy:
		ent = new TankEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("TankEnemy")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("TankEnemy_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(75.f);
		ent->GetStats().SetHP(3);
		break;
	case Types::EnemyBullet:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("EBullet")));
		ent->GetGraphic().AddAnimation("Idle", _ImgMan->GetAnimation("EBullet_Idle"));
		ent->GetGraphic().Swap("Idle");
		ent->GetPresence().SetYVel(150.f);
		ent->GetSize().SetSize(16.f, 16.f);
		break;
	case Types::Explosion:
		ent = new SFXEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Explosion")));
		ent->GetGraphic().AddAnimation("Explosion", _ImgMan->GetAnimation("Explosion"));
		ent->GetGraphic().Swap("Explosion");
		break;
	case Types::DoublePowerup:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("DoublePowerup")));
		ent->GetPresence().SetYVel(100.f);
		break;
	case Types::HealPowerup:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("HealPowerup")));
		ent->GetPresence().SetYVel(100.f);
		break;		
	case Types::LaserPowerup:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("LaserPowerup")));
		ent->GetPresence().SetYVel(100.f);
		break;
	case Types::InvinciblePowerup:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("InvinciblePowerup")));
		ent->GetPresence().SetYVel(100.f);
		break;
	case Types::Laser:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("LaserBeam")));
		ent->GetGraphic().GetSprPntr()->setScale(1.f, _Level->GetSize().GetHeight() / ent->GetGraphic().GetSprPntr()->getLocalBounds().height);
		break;
	case Types::BombPowerup:
		ent = new BasicEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Bomb")));
		ent->GetPresence().SetYVel(100.f);
		break;
	case Types::Boss:
		ent = new BossEnt(_Level);
		ent->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Boss")));
		ent->GetPresence().SetYVel(50.f);
		ent->GetPresence().SetPosition(x, y);
		ta = new BasicEnt(_Level);
		ta->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Turret")));
		ta->GetPresence().SetYVel(50.f);
		tb = new BasicEnt(_Level);
		tb->GetGraphic().SetSprite(sf::Sprite(*_ImgMan->GetTexturePntr("Turret")));
		tb->GetPresence().SetYVel(50.f);
		((BossEnt*)ent)->InitTurrets(ta, tb);
		break;
	default:
		ent = new BasicEnt(_Level);
		ent->GetSize().SetSize(25.f, 25.f);
		break;
	}

	ent->GetPresence().SetPosition(x, y);

	return ent;
};