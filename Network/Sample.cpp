#include "stdafx.h"
#include "Sample.h"




Sample::Sample(std::vector<long double> properties, std::string label)
{
	this->properties = properties;
	this->label = label;
}

Sample::~Sample()
{
}

int Sample::getSize()
{
	return this->properties.size();
}

long double Sample::operator[](const int index)
{
	return this->properties[index];
}

std::string Sample::getClass()
{
	return this->label;
}
