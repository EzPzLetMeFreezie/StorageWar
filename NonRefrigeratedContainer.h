#include "ContainerBase.h"

#pragma once

class NonRefrigeratedContainer : public ContainerBase
{
public:
	NonRefrigeratedContainer(ContainerID id);
	virtual ~NonRefrigeratedContainer() override;

	virtual const ContainerType getType() const override;
};
