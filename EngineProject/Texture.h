#pragma once
#include "Core.h"

class Texture {
public:
	Texture() {}
	Texture(GLuint tid)
	{
		this->id = tid;
	}

	bool operator<(Texture const& tex) const
	{
		if (this->id < tex.id)
			return true;
		else
			return false;
	}

	void operator=(Texture const& tex)
	{
		this->id = tex.id;
		this->transparent = tex.transparent;
		this->fakeLighting = tex.fakeLighting;
	}

	bool operator==(Texture const& tex)
	{
		return this->id == tex.id;
	}

	void SetTransparent(bool enable)
	{
		transparent = enable;
	}

	void SetFakeLighting(bool enable)
	{
		fakeLighting = enable;
	}

	bool GetTransparent()
	{
		return transparent;
	}

	bool GetFakeLighting()
	{
		return fakeLighting;
	}

	GLuint GetID()
	{
		return id;
	}
private:
	GLuint id;
	bool fakeLighting = false;
	bool transparent = false;
};