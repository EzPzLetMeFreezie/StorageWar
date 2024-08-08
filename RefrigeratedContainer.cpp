#include "ContainerBase.h"
#include "RefrigeratedContainer.h"

RefrigeratedContainer::RefrigeratedContainer(ContainerID id)
	: ContainerBase(id)
{
	m_isRefrigerated = true;
}

RefrigeratedContainer::~RefrigeratedContainer()
{
}

const ContainerType RefrigeratedContainer::getType() const
{
	return CT_Refrigerated;
}
