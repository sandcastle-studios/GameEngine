#pragma once
#include "Utilities\Container\GrowingArray.h"

namespace ENGINE_NAMESPACE
{

	class GameObject;
	class BaseComponentFactory;

	template <typename TComponentFactoryType>class ComponentFactory;

	class Camera;
	class CameraController;

	class Scene
	{
	public:
		Scene(const char* aName = "", const char* aSkyboxPath = nullptr);
		virtual ~Scene();

		virtual void Update(const Time & aDeltaTime);
		virtual void Render();

		void PushCameraController(const std::shared_ptr<CameraController> & aCameraController);

		template <typename TComponentType>
		void PreCreateComponentFactory();

		void UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const;

		std::shared_ptr<GameObject> CreateAndAddModel(const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		std::shared_ptr<GameObject> CreateObjectWithModel(const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		const Camera & GetCamera() const;

		void CreateGameObjectBuffer(const unsigned short aObjectCount);
		std::shared_ptr<GameObject>  CreateGameObject();

		template <typename TComponentType>
		std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory();

		template <typename TComponentType>
		const std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory()const;

		void IncrementRemovalCounter();
	protected:
		void SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection = Vector3f(0.f, 0.f, 1.f));

		//ComponentFactory<std::shared_ptr<ModelComponent>> myModelComponentFactory;
		GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

		GrowingArray<std::shared_ptr<GameObject>> myObjects;

		std::unique_ptr<ModelInstance> mySkybox;

		std::unique_ptr<Camera> myCamera;
		Stack<std::shared_ptr<CameraController>> myCameraControllers;
		
		Time myTime;
		std::string myName;

	private:
		int myScheduledRemovals;
	};

	template<typename TComponentType>
	inline void Scene::PreCreateComponentFactory()
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myFactories.Size() < nextID)
		{
			myFactories.Resize(nextID);
		}
		myFactories[id] = std::make_shared<ComponentFactory<TComponentType>>();
	}


	template <typename TComponentType>
	std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory()
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myFactories.Size() < nextID || myFactories[id] == nullptr)
		{
			PreCreateComponentFactory<TComponentType>();
		}
		return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);
	}

	template <typename TComponentType>
	const std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory() const
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);

	}

}
