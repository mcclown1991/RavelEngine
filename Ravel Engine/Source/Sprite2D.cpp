#include "Sprite2D.h"
#include "RavelEngine.h"
#include "GraphicsManager.h"
#include <rapidjson\stringbuffer.h>
#include <rapidjson\writer.h>

Sprite2D::Sprite2D() : RavelBehaviour(){
	m_Model = nullptr;
}

Sprite2D::~Sprite2D(){

}

void Sprite2D::LoadFromFile(std::string const& file)
{
	// do standard loading of component
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.IsObject()) {
		rapidjson::Value& sprite = doc["Sprite2D"];

		IsActive = sprite["IsActive"].GetBool();

		Vector2 pos;
		pos.x = sprite["Transform"]["X"].GetFloat();
		pos.y = sprite["Transform"]["Y"].GetFloat();

		transform->position = pos;

		std::string filepath = sprite["Texture"]["filepath"].GetString();
		Vector2 sz;
		sz.x = sprite["Texture"]["X"].GetFloat();
		sz.y = sprite["Texture"]["Y"].GetFloat();

		CreateTexture(filepath, sz.x, sz.y);
	}
}

void Sprite2D::Serialise()
{
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	rapidjson::Value root(rapidjson::kObjectType);

	rapidjson::Value base(rapidjson::kObjectType);
	base.AddMember("IsActive", IsActive, allocator);

	rapidjson::Value trans(rapidjson::kObjectType);
	rapidjson::Value tex(rapidjson::kObjectType);

	rapidjson::Value pos(rapidjson::kObjectType);
	pos.AddMember("X", transform->position.x, allocator);
	pos.AddMember("Y", transform->position.y, allocator);

	trans.AddMember("Transform", pos, allocator);

	rapidjson::Value sz(rapidjson::kObjectType);
	sz.AddMember("X", m_Model->hscale / 0.89f, allocator);
	sz.AddMember("Y", m_Model->vscale / 0.89f, allocator);

	tex.AddMember("Texture", sz, allocator);

	root.AddMember("Sprite2D", base, allocator);
	root.AddMember("Sprite2D", trans, allocator);
	root.AddMember("Sprite2D", tex, allocator);

	rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	doc.Accept(writer);

	std::string filename(gameObject->name + "_sprite2Dcustom.raveldata");
	std::ofstream out(filename, std::ofstream::out);

	out << doc.GetString();

	out.close();
}

void Sprite2D::Update(){
	//m_Sprite->SetScreenPosition(parent->position + transform->position);
}

void Sprite2D::OnDestory(){
	//HGE* h = RavelEngine::GetRavelEngine()->GetHGE();
	//delete m_Sprite;
	if(m_Model)
		m_Model->~Transform();
	this->~Sprite2D();
}

void Sprite2D::CreateTexture(std::string texture, float width, float height){
	GetGraphicsManager()->Renderer()->CreateTexture(texture, m_SampleID);
	m_Model = factory()->CreateComponent<Transform>();
	m_Model->hscale = width * 0.89f;
	m_Model->vscale = height * 0.89f;
	m_UV = Vector2(0.f, 0.f);
	m_Size = Vector2(1, 1);

	m_Dimension = Vector2(width, height);

	GetGraphicsManager()->AddSprite(this);
}

void Sprite2D::Render(){

	//Find Position, Rotation and Scale then transform
	//assume a reference frome from center of this sprite first
	Matrix4x4 trans = transform->GetTransforms() * m_Model->GetLocalTransforms();
	//trans = m_Reference_Frame * trans;
	//Vector2 vertice[4];

	/*vertice[0] = trans * m_Vertex[0];
	vertice[1] = trans * m_Vertex[1];
	vertice[2] = trans * m_Vertex[2];
	vertice[3] = trans * m_Vertex[3];*/

	GetGraphicsManager()->Renderer()->Render(m_SampleID, trans, m_UV, m_Size, true, 1);

	//vertice[0] = m_Reference_Frame * vertice[0];
	//vertice[1] = m_Reference_Frame * vertice[1];
	//vertice[2] = m_Reference_Frame * vertice[2];
	//vertice[3] = m_Reference_Frame * vertice[3];

	//(*m_Sprite)->Render(view, parent->localEulerAngles + transform->localEulerAngles, transform->hscale, transform->vscale);

	//(*m_Sprite)->Render(vertice);
}