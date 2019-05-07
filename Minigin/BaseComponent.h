#pragma once


namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;

		virtual void Update() {};
		virtual void Render() {};

		void SetParentObject(GameObject* object);
		GameObject* GetParentObject() const;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	private:
		GameObject* mParentObject;
	};

}

