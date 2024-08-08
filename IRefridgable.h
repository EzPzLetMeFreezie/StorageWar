#include "StorableObject.h"

#pragma once

class IRefridgable
{
public:
	virtual const bool isRefrigerated() const = 0 { return true; }
	const float getTemperature() { return m_temperature; }
private:
	float m_temperature = 0.f;
};
