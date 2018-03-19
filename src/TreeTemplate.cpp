#include "TreeTemplate.h"
#include "NodeTemplate.h"
#include "Element.h"
#include "Attribute.h"
#include "GameLib\GameLib.h"
#include "GraphicsDatabase.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
TreeTemplate::TreeTemplate(const Element & e,const GraphicsDatabase& db):
	_nodes(0),
	_nodeNumber(0)
{



	//ツリーなのか確認してる
	ASSERT(string("Tree") == *e.getName());
	//ルートノード（一番上のヤツが一つかどうか）
	ASSERT(e.getChildNumber() == 1);
	int an = e.getAttributeNumber();

	const string nameStr("name");
	cout << "TreeAttributeSize:" << an << endl;
	for (int i = 0; i < an; ++i) {
		const Attribute* a = e.getAttribute(i);
		if (nameStr == *a->getName()) {
			cout << "test" << i << endl;
			_name = *a->getValue();
			cout <<"addTreename" << a->getValue()->c_str() << endl;

		}
	}
	


	const Element* c = e.getChild(0);//根ノード取得
	//ノード数える

	_nodeNumber = countNode(*c, 0);


	cout << _name.c_str() << "'sNodeNumber" << _nodeNumber << endl;

	_nodes = new NodeTemplate[_nodeNumber];
	build(*c, db, 0);
}

TreeTemplate::~TreeTemplate()
{
	SAFE_DELETE_ARRAY(_nodes);
}

int TreeTemplate::getNodeNumber() const
{
	return _nodeNumber;
}

const NodeTemplate * TreeTemplate::getNode(int i) const
{
	ASSERT(0 <= i&& i < _nodeNumber);
	return &_nodes[i];
}

const string * TreeTemplate::getName() const
{
	return &_name;
}

int TreeTemplate::countNode(const Element& e, int n)
{
	++n;
	int cn = e.getChildNumber();
	cout << e.getAttribute(0)->getValue()->c_str() << "'s childNum is " << cn <<endl;
	for (int i = 0; i < cn; ++i) {
		cout<< "================" << e.getAttribute(0)->getValue()->c_str() << "'s child[" << i <<"]======"<< endl;
		const Element* childElement = e.getChild(i);
		ASSERT(string("Node") == *childElement->getName());
		n = countNode(*childElement, n);
		cout << e.getAttribute(0)->getValue()->c_str() << "'s child[" << i << "] end ======" << endl;
	}
	cout << "ret" << n << endl;

	return n;
}

int TreeTemplate::build(const Element& e, const GraphicsDatabase&  database, int nodePos)
{
	int an = e.getAttributeNumber();
	NodeTemplate& node = _nodes[nodePos];
	for (int i = 0; i < an; ++i) {
		const Attribute* a = e.getAttribute(i);
		string name = *a->getName();
		cout << "NodeTAttribute:" << a->getName()->c_str() << endl;
		if (name == "name") {
			node._name = *a->getValue();
		}
		else if (name == "batch") {
			node._batch = database.getBatch(a->getValue()->c_str());
		}
		else if (name == "translation") {
			a->getDoubleValues(&node._transration.x, 3);
		}
		else if (name == "rotation") {
			a->getDoubleValues(&node._rotation.x, 3);
		}
		else if (name == "scale") {
			a->getDoubleValues(&node._scale.x, 3);
		}
	}
	++nodePos;
	ASSERT(nodePos <= _nodeNumber);
	int cn = e.getChildNumber();
	int elder = -1;
	for (int i = 0; i < cn; ++i) {
		const Element* c = e.getChild(i);
		if (i == 0) {
			node._oldestChild = nodePos;
		}
		else {
			_nodes[elder]._youngerBrother = nodePos;
		}
		elder = nodePos;
		nodePos = build(*c, database, nodePos);
	}
	cout << "unko" << endl;
	return nodePos;
	
}
string* TreeTemplate::debugString() {
	return 0;
}