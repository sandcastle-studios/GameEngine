#pragma once
#include "Engine\LightConstantBufferData.h"

namespace ENGINE_NAMESPACE
{

	class GenericMesh;
	template<typename T>
	class VertexBuffer;
	class ModelInstance;

	template <typename T>
	class ConstantBuffer;

	class Effect;

	class TextureCube;

	class BatchEntry
	{
	public:
		BatchEntry(const std::shared_ptr<const GenericMesh> & aMesh);
		void Schedule();
		bool IsScheduled();

		void AddInstance(const std::shared_ptr<Effect> & aEffect, const Matrix44f & aMatrix);
		void FinishedRendering();

		struct MatricesContainer
		{
			GrowingArray<Matrix44f> matrices;
			std::shared_ptr<Effect> effect;
			unsigned short matrixCounter;
		};

		const GrowingArray<MatricesContainer> & GetMatricesContainers() const;

		const GenericMesh & GetMesh() const;

	private:
		std::weak_ptr<const GenericMesh> myMesh;
		std::shared_ptr<const GenericMesh> myMeshScheduleLock;
		
		GrowingArray<MatricesContainer> myMatrices;
		int myEffectCounter;
	};

	class ModelRenderer
	{
	public:
		ModelRenderer();
		~ModelRenderer();

		void InstantRender(const std::shared_ptr<Effect>& aEffect, const std::shared_ptr<GenericMesh> & myMeshes);
		void Render(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh, const Matrix44f & aMatrix);
		void RenderBuffer();

		void PrepareInstantRender(const Matrix44f & aWorldMatrix);

		void Schedule(BatchEntry & aBatch);

		size_t GenerateBatchIdentifier(const std::shared_ptr<GenericMesh> & aMesh);
		void ReturnBatchIdentifier(size_t aBatchIdentifier);

		void SetAmbient(float aAmbient);
		void SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor);

		float GetAmbient() const;

	private:
		std::vector<BatchEntry*> myCurrentlyScheduledBatches;
		std::vector<std::unique_ptr<BatchEntry>> myMeshes;
		std::stack<size_t> myReturnedBatchIdentifiers;
		std::vector<std::shared_ptr<VertexBuffer<Matrix44f>>> myVertexBuffers;

		std::shared_ptr<ConstantBuffer<LightConstantBufferData>> myLightingBuffer;
		LightConstantBufferData myLightingData;

		std::shared_ptr<TextureCube> mySkybox;
		std::shared_ptr<Effect> myEffect;

		bool myIsInstantRendering;
		void UpdateAndBindLightingBuffer();
	};

}
