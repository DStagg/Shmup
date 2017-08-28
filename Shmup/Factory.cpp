#include "Factory.h"

EntFactory::EntFactory()
{

};

void EntFactory::Init(ImageManager* img, sf::RenderWindow* rw)
{
	_ImgMan = img;
	_Window = rw;
};

Entity* EntFactory::Spawn(int type, float x, float y)
{
	Entity* ent;

	switch (type)
	{
	case Types::Player:
		ent = new PlayerEnt(_Window);
		ent->GetStats().SetMaxHP(5);
		ent->GetStats().SetHP(5);
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("Player")), _ImgMan->GetAnimation("Player_Idle")));
		break;
	case Types::PlayerBullet:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("PBullet")), _ImgMan->GetAnimation("PBullet_Idle")));
		ent->GetPresence().SetYVel(-300.f);
		break;
	case Types::BombEnemy:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("BombEnemy")), _ImgMan->GetAnimation("BombEnemy_Idle")));
		ent->GetPresence().SetYVel(125.f);
		break;
	case Types::DroneEnemy:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("DroneEnemy")), _ImgMan->GetAnimation("DroneEnemy_Idle")));
		ent->GetPresence().SetYVel(100.f);
		ent->GetStats().SetHP(2);
		break;
	case Types::SpreaderEnemy:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("SpreaderEnemy")), _ImgMan->GetAnimation("SpreaderEnemy_Idle")));
		ent->GetPresence().SetYVel(100.f);
		ent->GetStats().SetHP(2);
		break;
	case Types::SwarmEnemy:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("SwarmEnemy")), _ImgMan->GetAnimation("SwarmEnemy_Idle")));
		ent->GetPresence().SetYVel(150.f);
		break;
	case Types::TankEnemy:
		ent = new Entity();
		ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan->GetTexturePntr("TankEnemy")), _ImgMan->GetAnimation("TankEnemy_Idle")));
		ent->GetPresence().SetYVel(75.f);
		ent->GetStats().SetHP(3);
		break;
	default:
		ent = new Entity();
		ent->GetSize().SetSize(25.f, 25.f);
		ent->SetIcon(new RectIcon(ent, sf::Color::Cyan));
		break;
	}

	ent->GetPresence().SetPosition(x, y);

	return ent;
};