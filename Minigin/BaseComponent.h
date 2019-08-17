#pragma once


namespace dae
{
	class GameObject;

	enum class CompType
	{
		Camera,
		FPS,
		Input,
		Render,
		Script,
		Text,
		Transform, 
		Texture,
		FSM,
		Grid,
		Subject
	};

	class BaseComponent
	{
	public:
		BaseComponent(CompType compType);
		virtual ~BaseComponent() = default;

		virtual void Init() {};
		virtual void Update() {};

		void SetGameObject(GameObject* object);
		GameObject* GetGameObject() const;
		CompType GetComponentType();

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	private:
		GameObject* m_GameObject;
		CompType m_CompType;
	};

}

