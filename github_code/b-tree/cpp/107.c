#include "OBehaviorTree.h"

USING_NS_O;

/********BehaviorTreeNode*******/
BehaviorTreeNode::BehaviorTreeNode(const std::string&type) :_type(type)
{
}

BehaviorTreeNode::~BehaviorTreeNode()
{

}

bool BehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
	return false;
}

/**************CompositeBehaviorTreeNode************/
const std::string CompositeBehaviorTreeNode::TYPE = "composite";
CompositeBehaviorTreeNode::CompositeBehaviorTreeNode(const std::string&compositeType)
	:BehaviorTreeNode(CompositeBehaviorTreeNode::TYPE)
	, _compositeType(compositeType)
{

}

CompositeBehaviorTreeNode::~CompositeBehaviorTreeNode()
{
	std::vector<BehaviorTreeNode *>::iterator iter = _children.begin();
	for (iter; iter != _children.end(); ++iter)
	{
		CC_SAFE_DELETE(*iter);
	}
	_children.clear();
}

bool CompositeBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
#ifdef ORIGIN_BEHAVIOR_TREE_DEBUG
	CCLOG("behaviorTreeNode compositeType=%s  name=%s execute", _compositeType.c_str(), _name.c_str());
#endif
	return false;
}
/*************DecoratorBehaviorTreeNode*************/
const std::string DecoratorBehaviorTreeNode::TYPE = "decorator";
DecoratorBehaviorTreeNode::DecoratorBehaviorTreeNode(const std::string&decoratorType)
	:BehaviorTreeNode(DecoratorBehaviorTreeNode::TYPE)
	, _decoratorType(decoratorType), _child(nullptr)
{

}

DecoratorBehaviorTreeNode::~DecoratorBehaviorTreeNode()
{
	if (_child != nullptr) CC_SAFE_DELETE(_child);
}

bool DecoratorBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
#ifdef ORIGIN_BEHAVIOR_TREE_DEBUG
	CCLOG("behaviorTreeNode decoratorType=%s  name=%s execute", _decoratorType.c_str(), _name.c_str());
#endif
	return false;
}

/***************ConditionBehaviorTreeNode**************/
const std::string ConditionBehaviorTreeNode::TYPE = "condition";
ConditionBehaviorTreeNode::ConditionBehaviorTreeNode(const std::string&conditionType) :BehaviorTreeNode(ConditionBehaviorTreeNode::TYPE), _conditionType(conditionType)
{

}

ConditionBehaviorTreeNode::~ConditionBehaviorTreeNode()
{

}

bool ConditionBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
#ifdef ORIGIN_BEHAVIOR_TREE_DEBUG
	CCLOG("behaviorTreeNode conditionType=%s  name=%s execute", _conditionType.c_str(), _name.c_str());
#endif
	return false;
}
/**************ActionBehaviorTreeNode***************/
const std::string ActionBehaviorTreeNode::TYPE = "action";
ActionBehaviorTreeNode::ActionBehaviorTreeNode(const std::string&actionType) :BehaviorTreeNode(ActionBehaviorTreeNode::TYPE), _actionType(actionType)
{

}

ActionBehaviorTreeNode::~ActionBehaviorTreeNode()
{

}

bool ActionBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
#ifdef ORIGIN_BEHAVIOR_TREE_DEBUG
	CCLOG("behaviorTreeNode actionType=%s  name=%s execute", _actionType.c_str(), _name.c_str());
#endif
	return false;
}

/***************SelectorBehaviorTreeNode***************/
const std::string SelectorBehaviorTreeNode::TYPE = "selector";
SelectorBehaviorTreeNode::SelectorBehaviorTreeNode(const std::string&compositeType) :CompositeBehaviorTreeNode(compositeType)
{

}

SelectorBehaviorTreeNode::~SelectorBehaviorTreeNode()
{

}

bool SelectorBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
	CompositeBehaviorTreeNode::execute(event);

	for (auto node : _children)
	{
		if (node->execute(event))
			return true;
	}
	return false;
}

/********************SequenceBehaviorTreeNode*******************/
const std::string SequenceBehaviorTreeNode::TYPE = "sequence";
SequenceBehaviorTreeNode::SequenceBehaviorTreeNode(const std::string&compositeType) :CompositeBehaviorTreeNode(compositeType)
{

}

SequenceBehaviorTreeNode::~SequenceBehaviorTreeNode()
{

}

bool SequenceBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
	CompositeBehaviorTreeNode::execute(event);

	for (auto node : _children)
	{
		if (node->execute(event))
			return false;
	}
	return true;
}

/*******************TurnBehaviorTreeNode************************/
const std::string TurnBehaviorTreeNode::TYPE = "turn";
TurnBehaviorTreeNode::TurnBehaviorTreeNode(const std::string&decoratorType) :DecoratorBehaviorTreeNode(decoratorType)
{

}

TurnBehaviorTreeNode::~TurnBehaviorTreeNode()
{

}

bool TurnBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
	DecoratorBehaviorTreeNode::execute(event);

	return !_child->execute(event);
}

/********************EventConditionBehaviorTreeNode*******************/
const std::string EventConditionBehaviorTreeNode::TYPE = "eventCondition";
EventConditionBehaviorTreeNode::EventConditionBehaviorTreeNode(const std::string&eventName, const std::string&conditionType) 
	:ConditionBehaviorTreeNode(conditionType)
	, _eventName(eventName)
{

}

EventConditionBehaviorTreeNode::~EventConditionBehaviorTreeNode()
{

}

bool EventConditionBehaviorTreeNode::execute(cocos2d::EventCustom * event) const
{
	ConditionBehaviorTreeNode::execute(event);

	if (event->getEventName() == _eventName)
	{
		return true;
	}
	return false;
}

/*****************BehaviorTreesDefiniation*****************/
#define ORIGIN_BEHAVIOR_TREE_TAG_TREES				"trees"
#define ORIGIN_BEHAVIOR_TREE_TAG_ROOT				"root"
#define ORIGIN_BEHAVIOR_TREE_TAG_ID					"id"
#define ORIGIN_BEHAVIOR_TREE_TAG_TYPE				"type"
#define ORIGIN_BEHAVIOR_TREE_TAG_COMPOSITE_TYPE		"compositeType"
#define ORIGIN_BEHAVIOR_TREE_TAG_CHILDREN			"children"
#define ORIGIN_BEHAVIOR_TREE_TAG_DECORATOR_TYPE		"decoratorType"
#define ORIGIN_BEHAIVOR_TREE_TAG_CHILD				"child"
#define ORIGIN_BEHAIVOR_TREE_TAG_CONDITION_TYPE		"conditionType"
#define ORIGIN_BEHAVIOR_TREE_TAG_EVENT_NAME			"eventName"
#define ORIGIN_BEHAIVOR_TREE_TAG_ACTION_TYPE		"actionType"

BehaviorTreesDefiniation::BehaviorTreesDefiniation()
{

}

BehaviorTreesDefiniation::~BehaviorTreesDefiniation()
{
	std::vector<BehaviorTreeDefiniation *>::iterator iter = _trees.begin();
	for (iter; iter != _trees.end(); ++iter)
	{
		CC_SAFE_DELETE(*iter);
	}
	_trees.clear();
}

void BehaviorTreesDefiniation::parse(const std::string&data)
{
	//
	rapidjson::Document document;
	document.Parse(data.c_str());

	size_t n = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(document, ORIGIN_BEHAVIOR_TREE_TAG_TREES);
	for (int i = 0; i < n; i++)
	{
		const rapidjson::Value&treeValue = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(document, ORIGIN_BEHAVIOR_TREE_TAG_TREES, i);
		
		BehaviorTreeDefiniation * treeDefiniation = new BehaviorTreeDefiniation;
		treeDefiniation->parse(treeValue);
		_trees.push_back(treeDefiniation);
	}
}

/********************BehaviorTreeDefiniation******************/
BehaviorTreeDefiniation::BehaviorTreeDefiniation()
{

}

BehaviorTreeDefiniation::~BehaviorTreeDefiniation()
{
	if (_root != nullptr) CC_SAFE_DELETE(_root);
}

void BehaviorTreeDefiniation::parse(const rapidjson::Value&data)
{
	unsigned int id = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(data, ORIGIN_BEHAVIOR_TREE_TAG_ID);
	const rapidjson::Value&rootValue = cocostudio::DictionaryHelper::getInstance()->getSubDictionary_json(data, ORIGIN_BEHAVIOR_TREE_TAG_ROOT);
	BehaviorTreeNodeParse nodeParse = getNodeParse();
	BehaviorTreeNode * node = nodeParse.parse(rootValue);
	setRoot(node);
}

BehaviorTreeNodeParse BehaviorTreeDefiniation::getNodeParse()
{
	BehaviorTreeNodeParse nodeParse;
	return nodeParse;
}

/****************************BehaviorTreeNodeParse************************/
BehaviorTreeNodeParse::BehaviorTreeNodeParse()
{

}

BehaviorTreeNodeParse::~BehaviorTreeNodeParse()
{

}

BehaviorTreeNode * BehaviorTreeNodeParse::parse(const rapidjson::Value&data)
{
	std::string type = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(data, ORIGIN_BEHAVIOR_TREE_TAG_TYPE);
	if (type == CompositeBehaviorTreeNode::TYPE)
	{
		return parseCompositeBehaviorTreeNode(data);
	}
	else if (type == DecoratorBehaviorTreeNode::TYPE)
	{
		return parseDecoratorBehaviorTreeNode(data);
	}
	else if (type == ConditionBehaviorTreeNode::TYPE)
	{
		return parseConditionBehaviorTreeNode(data);
	}
	else if (type == ActionBehaviorTreeNode::TYPE)
	{
		return parseActionBehaviorTreeNode(data);
	}
	return nullptr;
}

CompositeBehaviorTreeNode * BehaviorTreeNodeParse::parseCompositeBehaviorTreeNode(const rapidjson::Value&data)
{
	std::string compositeType = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(data, ORIGIN_BEHAVIOR_TREE_TAG_COMPOSITE_TYPE);
	if (compositeType == SelectorBehaviorTreeNode::TYPE)
	{
		std::vector<BehaviorTreeNode *> children;
		size_t n = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(data, ORIGIN_BEHAVIOR_TREE_TAG_CHILDREN);
		for (size_t i = 0; i < n; i++)
		{
			const rapidjson::Value&childValue = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(data, ORIGIN_BEHAVIOR_TREE_TAG_CHILDREN, i);
			BehaviorTreeNode * treeNode = parse(childValue);
			children.push_back(treeNode);
		}
		SelectorBehaviorTreeNode * selector = new SelectorBehaviorTreeNode;
		selector->setChildren(children);
		return selector;
	}
	else if (compositeType == SequenceBehaviorTreeNode::TYPE)
	{
		std::vector<BehaviorTreeNode *> children;
		size_t n = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(data, ORIGIN_BEHAVIOR_TREE_TAG_CHILDREN);
		for (size_t i = 0; i < n; i++)
		{
			const rapidjson::Value&childValue = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(data, ORIGIN_BEHAVIOR_TREE_TAG_CHILDREN, i);
			BehaviorTreeNode * treeNode = parse(childValue);
			children.push_back(treeNode);
		}
		SequenceBehaviorTreeNode * sequence = new SequenceBehaviorTreeNode;
		sequence->setChildren(children);
		return sequence;
	}
	return nullptr;
}

DecoratorBehaviorTreeNode * BehaviorTreeNodeParse::parseDecoratorBehaviorTreeNode(const rapidjson::Value&data)
{
	std::string decoratorType = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(data, ORIGIN_BEHAVIOR_TREE_TAG_DECORATOR_TYPE);
	if (decoratorType == TurnBehaviorTreeNode::TYPE)
	{
		BehaviorTreeNode * child = nullptr;
		const rapidjson::Value&childValue = cocostudio::DictionaryHelper::getInstance()->getSubDictionary_json(data, ORIGIN_BEHAIVOR_TREE_TAG_CHILD);
		child = parse(childValue);
		TurnBehaviorTreeNode * decorator = new TurnBehaviorTreeNode;
		decorator->setChild(child);
		return decorator;
	}
	return nullptr;
}

ConditionBehaviorTreeNode * BehaviorTreeNodeParse::parseConditionBehaviorTreeNode(const rapidjson::Value&data)
{
	std::string conditionType = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(data, ORIGIN_BEHAIVOR_TREE_TAG_CONDITION_TYPE);
	if (conditionType == EventConditionBehaviorTreeNode::TYPE)
	{
		std::string eventName = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(data, ORIGIN_BEHAVIOR_TREE_TAG_EVENT_NAME);
		EventConditionBehaviorTreeNode * condition = new EventConditionBehaviorTreeNode(eventName);
		return condition;
	}
	return nullptr;
}

ActionBehaviorTreeNode * BehaviorTreeNodeParse::parseActionBehaviorTreeNode(const rapidjson::Value&data)
{
	return nullptr;
}