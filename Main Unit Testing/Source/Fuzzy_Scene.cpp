#include "Fuzzy_Scene.h"
#include "Input.h"
#include "Timer.h"
#include "Timer.cpp"
#include "ComponentHeader.h"

Fuzzy_Scene Fuzzy_Scene::_Scene;

void Fuzzy_Scene::Init()
{
	GetGraphicsManager()->SetVertexShader("Shaders\\Texture");
	GetGraphicsManager()->SetFragmentShader("Shaders\\Fragments");
	GetGraphicsManager()->LinkProgram();

	// register all custom components first before loading all prefabs
	//factory()->RegisterComponent<Button<Fuzzy_Scene>>("Button<Fuzzy_Scene>");

	factory()->LoadFromFile("gameobject.raveldata");
	Factory::pGameObject& obj = factory()->GetGameObject("testJson");
	Button<Fuzzy_Scene>* button = obj->GetComponent<Button<Fuzzy_Scene>>();
	button->Initialise(this);
	button->AddLisenter(&Fuzzy_Scene::Load);

	//Factory::pGameObject& m_Test = factory()->CreateGameObject("Test");
	//Sprite2D* m_spr = dynamic_cast<Sprite2D*>(m_Test->AddComponent("Sprite2D"));
	////Sprite2D* m_spr = m_Test->AddComponent<Sprite2D>();
	//m_spr->CreateTexture("Background.png", 1280, 720);
	//m_Test->transform->position = Vector2(0, 0);
	//m_trans = m_Test->transform;

	//Factory::pGOC& m_Door = factory()->CreateGameObject("Door");
	//m_spr = m_Door->AddComponent<Sprite2D>();
	//m_spr->CreateTexture("BlueDoor.png", 32, 64);
	//m_Door->transform->position = Vector2(-100, 0);
	//m_trans = m_Door->transform;
	////Script* m_Script = m_Door->AddComponent<Script>();
	////m_Script->LoadScript("test.lua");
	////m_Door->transform->Scale(2);
	////m_Door->transform->Rotate(45);
	//BoxCollider* col =  m_Door->AddComponent<BoxCollider>();
	//col->CreateBoxCollider();
	//Text* tx = m_Door->AddComponent<Text>();
	//tx->SetFontSize(20);
	//tx->_text = "Hello World";
	//factory()->RegisterComponent<Button<Fuzzy_Scene>>("Button");
	//Button<Fuzzy_Scene>* button = m_Door->AddComponent<Button<Fuzzy_Scene>>();
	//button->Initialise(this);
	//button->AddLisenter(&Fuzzy_Scene::Load);

	//Factory::pGOC& m_Door1 = factory()->CreateGameObject("Door1");
	//m_spr = m_Door1->AddComponent<Sprite2D>();
	//m_spr->CreateTexture("BlueDoor.png", 32, 64);
	//m_Door1->transform->position = Vector2(0, 0);
	////m_Door->transform->Scale(2);
	//m_Door1->transform->Rotate(45);
	//col = m_Door1->AddComponent<BoxCollider>();
	//col->CreateBoxCollider();
	

	/*xb = new XBOXController(1);
	if (xb->Refesh()) std::cout << "Refreshed";
	if (xb->IsConnected()) std::cout << "XBox controller is connected";

	Factory::pGOC& m_timer = factory()->CreateGameObject("timer1");
	Timer<Fuzzy_Scene>* r = m_timer->AddComponent<Timer<Fuzzy_Scene>>();
	r->CreateTimer(2, &Fuzzy_Scene::Load);
	r->CreateTimer(2, &Fuzzy_Scene::Load);
	r->CreateTimer(2, &Fuzzy_Scene::Load);
	r->CreateTimer(2, &Fuzzy_Scene::Load);
	r->CreateTimer(2, &Fuzzy_Scene::Load);*/
}

void Fuzzy_Scene::Load()
{
	
}

void Fuzzy_Scene::Update()
{
	//Text Updates
	/*if(OnKeyPress(VK_LEFT)){
		m_trans->position.x -= 1;
		std::cout << m_trans->position.x << std::endl;
	}
	if (OnKeyPress(VK_RIGHT)) {
		m_trans->position.x += 1;
		std::cout << m_trans->position.x << std::endl;
	}
	if (OnKeyPress(VK_UP)) {
		m_trans->position.y -= 1;
		std::cout << m_trans->position.x << std::endl;
	}
	if (OnKeyPress(VK_DOWN)) {
		m_trans->position.y += 1;
		std::cout << m_trans->position.x << std::endl;
	}

	if (OnKeyPress(VK_NUMPAD1)) {
		m_trans->Rotate(1);
		std::cout << m_trans->localEulerAngles << std::endl;
	}*/

	/*xb->GetState();
	xb->Vibrate(60000, 60000);
	if (!xb->Refesh()) {
		std::cout << "Not connected";
	}
	if (xb->LeftStickAngle() > 0)
		std::cout << "Dop";*/
}

void Fuzzy_Scene::Free()
{
	Factory::pGameObject& obj = factory()->GetGameObject("testJson");
	Sprite2D* spr = obj->GetComponent<Sprite2D>();
	spr->Serialise();
}

void Fuzzy_Scene::Unload()
{
}

void Fuzzy_Scene::Pause()
{
}

void Fuzzy_Scene::Resume()
{
}

void Fuzzy_Scene::ChangeState(GameStateManager * gsm, uInt32 btnType)
{
}

void Fuzzy_Scene::End(bool hit)
{
	
}
