#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Engine/BoundingBox.h>


namespace ENGINE_NAMESPACE
{
	class Model;
	class Effect;

	class ModelComponent : public BaseComponent
	{
	public:
		ModelComponent();
		~ModelComponent();

		virtual void Update(const Time & aDeltaTime) override;

		virtual void Render() const override;

		void SetModel(std::shared_ptr<Model> aModel);

		void SetModel(const char* aModelFilePath, std::shared_ptr<Effect> aEffect);

		const BoundingBoxf & GetBoundingBox() const;

		virtual void Construct() override;

		virtual void Destruct() override;

		void SetMatrix(const Matrix44f & aMatrix);

	private:
		std::shared_ptr<Model> myModel;
		Matrix44f myMatrix;
	};
}
