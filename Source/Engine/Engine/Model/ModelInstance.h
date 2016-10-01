#pragma once


namespace ENGINE_NAMESPACE
{
	class Model;
	class Effect;

	class ModelInstance
	{
	public:
		ModelInstance(const std::shared_ptr<Model> & aModel);
		~ModelInstance();

		void SetEffect(const std::shared_ptr<Effect> & aEffect);
		const std::shared_ptr<Effect> & GetEffect() const;

		void Render() const;
		void InstantRender() const;

		void SetMatrix(const Matrix44f & aMatrix);
		const Matrix44f & GetMatrix() const;

		void SetPosition(const Vector3f & aPosition);
		Vector3f GetPosition() const;

		const std::shared_ptr<Model> & GetModel();
		const std::shared_ptr<const Model> & GetModel() const;

		BoundingBoxf GetBoundingBox() const;

	private:
		Matrix44f myWorldMatrix;
		std::shared_ptr<Model> myModel;
		std::shared_ptr<Effect> myEffect;
	};

	inline const Matrix44f & ModelInstance::GetMatrix() const
	{
		return myWorldMatrix;
	}

	inline void ModelInstance::SetPosition(const Vector3f & aPosition)
	{
		myWorldMatrix.SetPosition(aPosition);
	}

	inline Vector3f ModelInstance::GetPosition() const
	{
		return myWorldMatrix.GetPosition();
	}

	inline const std::shared_ptr<Model> & ModelInstance::GetModel()
	{
		return myModel;
	}

	inline const std::shared_ptr<const Model> & ModelInstance::GetModel() const
	{
		return myModel;
	}
}
