#include "NodeTemplate.h"

NodeTemplate::NodeTemplate():
	_oldestChild(-1),
	_youngerBrother(-1),
	_batch(0),
	_transration(0,0,0),
	_rotation(0,0,0),
	_scale(1.0,1.0,1.0)
{
}

NodeTemplate::~NodeTemplate()
{
}

int NodeTemplate::getChild() const
{
	return _oldestChild;
}

int NodeTemplate::getBrother() const
{
	return _youngerBrother;
}

const Batch * NodeTemplate::getBatch() const
{
	return _batch;
}

const Vector3D * NodeTemplate::getTranslation() const
{
	return &_transration;
}

const Vector3D * NodeTemplate::getRotation() const
{
	return &_rotation;
}

const Vector3D * NodeTemplate::getScale() const
{
	return &_scale;
}

const string * NodeTemplate::getName() const
{
	return &_name;
}
