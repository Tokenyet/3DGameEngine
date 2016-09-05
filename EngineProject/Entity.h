#pragma once
#include "Core.h"
#include "TextureModel.h"
template <class T>
class Entity
{
public:
	Entity(T model, glm::vec3 position, float rx, float ry, float rz, float scale);
	void MovePosition(float dx, float dy, float dz);
	void MoveRotation(float dx, float dy, float dz);
	T GetModel();
	glm::vec3 GetPosition();
	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();
	float GetScale();
	~Entity();
private:
	T model;
	glm::vec3 position;
	float rx, ry, rz; // degree
	float scale;
};	

template <class T>
Entity<T>::~Entity()
{
}

template <class T>
Entity<T>::Entity(T model, glm::vec3 position, float rx, float ry, float rz, float scale)
{
	this->model = model;
	this->position = position;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->scale = scale;
}

template <class T>
void Entity<T>::MovePosition(float dx, float dy, float dz)
{
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

template <class T>
void Entity<T>::MoveRotation(float dx, float dy, float dz)
{
	this->rx += dx;
	this->ry += dy;
	this->rz += dz;
}

template <class T>
T Entity<T>::GetModel()
{
	return this->model;
}

template <class T>
glm::vec3 Entity<T>::GetPosition()
{
	return this->position;
}

template <class T>
float Entity<T>::GetRotationX()
{
	return this->rx;
}

template <class T>
float Entity<T>::GetRotationY()
{
	return this->ry;
}

template <class T>
float Entity<T>::GetRotationZ()
{
	return this->rz;
}

template <class T>
float Entity<T>::GetScale()
{
	return this->scale;
}
