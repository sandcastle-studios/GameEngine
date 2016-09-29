#pragma once

class GameObject;

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent() = 0;

	virtual void Update(const Time & aDeltaTime);

	virtual void Render() const;

	virtual void Construct() = 0;
	virtual void Destruct() = 0;

	void SetGameObject(GameObject & anObject);
	 
protected:
	GameObject * myObject;
};

