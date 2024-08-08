#include "ContainerBase.h"
#include "NonRefrigeratedContainer.h"

NonRefrigeratedContainer::NonRefrigeratedContainer(ContainerID id)
	: ContainerBase(id)
{
	m_IsRefrigerated = false;
}

NonRefrigeratedContainer::~NonRefrigeratedContainer()
{
}

const ContainerType NonRefrigeratedContainer::getType() const
{
	return CT_NonRefrigerated;
}
