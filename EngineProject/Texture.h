#pragma once
#include "Core.h"

class Texture {
public:
	const GLuint &ID;
	Texture() :ID(id) {}
	Texture(GLuint tid) :ID(id)
	{
		this->id = tid;
	}
	bool operator<(Texture const& tex) const
	{
		if (ID < tex.ID)
			return true;
		else
			return false;
	}
	void operator=(Texture const& tex)
	{
		this->id = tex.id;
	}
	bool operator==(Texture const& tex) const
	{
		return this->ID == tex.ID;
	}
private:
	GLuint id;
};