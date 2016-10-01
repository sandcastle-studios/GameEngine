#pragma once

namespace ENGINE_NAMESPACE
{

	class GenericMesh;
	class Effect;

	class Model
	{
	public:
		Model();
		Model(const std::shared_ptr<GenericMesh> & aMesh);
		virtual ~Model();

		void Render(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aMatrix) const;
		void InstantRender(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix) const;

		const std::vector<std::shared_ptr<GenericMesh>> & GetMeshes() const;

		const BoundingBoxf & GetBoundingBox() const;

	protected:
		void AddMesh(const std::shared_ptr<GenericMesh> & aMesh);

	private:
		std::vector<std::shared_ptr<GenericMesh>> myMeshes;
		BoundingBoxf myBoundingBox;
	};
}
