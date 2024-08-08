#include "ContainerBase.h"
#include "NonRefrigeratedContainer.h"

NonRefrigeratedContainer::NonRefrigeratedContainer(ContainerID id)
	: ContainerBase(id)
{
	m_isRefrigerated = false;
}

NonRefrigeratedContainer::~NonRefrigeratedContainer()
{
}

const ContainerType NonRefrigeratedContainer::getType() const
{
	return CT_NonRefrigerated;
}
