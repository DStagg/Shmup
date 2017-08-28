#include "Factory.h"

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
	default:
		ent = new BasicEnt(_Level);
		ent->GetSize().SetSize(25.f, 25.f);
		break;
	}

	ent->GetPresence().SetPosition(x, y);

	return ent;
};