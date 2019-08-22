#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class SubjectComponent final : public dae::BaseComponent
	{
	public:
		SubjectComponent();
		~SubjectComponent() override;

		void Update() override;

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

		void Notify(dae::GameObject* gameObject, const std::string& message);

		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;

	private:

		Subject* m_pSubject;
	};
}

