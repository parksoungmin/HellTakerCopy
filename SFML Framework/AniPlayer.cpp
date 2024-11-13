#include "stdafx.h"
#include "AniPlayer.h"
#include "AnimationClip.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);

}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);

}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);

}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	Idle();
	Jumping();
	Runing();



	animator.Play(&idle);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play(&idle);
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		animator.Play("animations/jump.csv");
		animator.PlayQueue("animations/Idle.csv");
	}




	float h = 0.f;
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;
	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		velocity.y = -500.f;
		animator.Play(&jump);
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (position.y > 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.0f));
	}

	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play(&run);
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play(&idle);
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play(&idle);
		}
		else
		{
			animator.Play(&run);
		}
	}

	//if (isJumping)
	//{
	//	isJumping = animator.IsPlaying();
	//}
	//if (InputMgr::GetKey(sf::Keyboard::Space))
	//{
	//	SetJumping(true);
	//	animator.Play(&jump);
	//}

	//if (!isJumping)
	//{
	//	if (InputMgr::GetAxis(Axis::Horizontal) != 0)
	//	{
	//		animator.Play(&run);
	//		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	//		{
	//			auto a = body.getScale();
	//			if(a.x > 0)
	//			a.x *= -1;
	//			body.setScale(a);
	//			auto b = body.getPosition();
	//			b.x -= 10;
	//			body.setPosition(b);
	//		}	
	//		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	//		{
	//			auto a = body.getScale();
	//			if(a.x < 0)
	//			a.x *= -1;
	//			body.setScale(a);
	//			auto b = body.getPosition();
	//			b.x += 10;
	//			body.setPosition(b);
	//		}
	//	}
	//	else
	//	{
	//		animator.Play(&idle);
	//	}
	//}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniPlayer::Idle()
{

	std::string sheetId = "graphics/sprite_sheet.png";
	sf::IntRect coord(0, 0, 120, 120);

	idle.loadFromFile("Animations/idle.csv");

}

void AniPlayer::Jumping()
{
	std::string sheetId = "graphics/sprite_sheet.png";
	sf::IntRect coord(0, 360, 120, 120);

	// jump 
	jump.loadFromFile("Animations/jump.csv");
}

void AniPlayer::SetJumping(bool jm)
{
	isJumping = jm;
}

void AniPlayer::Runing()
{
	std::string sheetId = "graphics/sprite_sheet.png";
	sf::IntRect coord(0, 120, 120, 120);

	// run 
	run.loadFromFile("Animations/run.csv");
}