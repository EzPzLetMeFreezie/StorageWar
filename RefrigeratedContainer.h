#include "ContainerBase.h"

#pragma once

class RefrigeratedContainer : public ContainerBase
{
public:
	RefrigeratedContainer(ContainerID id);
	virtual ~RefrigeratedContainer() override;

	virtual const ContainerType getType() const override;
};
