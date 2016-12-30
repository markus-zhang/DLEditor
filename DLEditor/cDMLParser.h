/*	Dragonlance Project
	Experimental Dragonlance Meta Language Parser
*/

#ifndef CDMLPARSER_H_
#define CDMLPARSER_H_

#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "DebugTool.h"

struct cDMLObject
{
	std::string m_Tag;
	std::string m_Parameter;
	std::string m_ParameterValue;
	std::string m_Value;
};

template<class T>
class cTreeNode
{
protected:
	T							m_NodeContent;
	std::vector<cTreeNode<T>*>	m_Children;
public:
	// Constructor & Destructor
	cTreeNode() {}
	cTreeNode(const T& node_content) : m_NodeContent(node_content) {}
	cTreeNode(const T& node_content,
		std::vector< cTreeNode<T>* >& children) :
		m_NodeContent(node_content), m_Children(children) {}
	~cTreeNode() {}

	// Accessor
	inline const T& GetNodeContent() const
	{
		return m_NodeContent;
	}

	inline std::vector<cTreeNode<T>*>& GetChildren() const
	{
		return m_Children;
	}

	// Mutator
	inline void SetNodeContent(T node_content)
	{
		m_NodeContent = node_content;
	}
};

class cDMLObjectNode : public cTreeNode<cDMLObject>
{
private:
	cTreeNode<cDMLObject>* m_RootPrt;
	std::vector<cDMLObjectNode*> m_Children;
	cTreeNode<cDMLObject>* m_CurrentDMLNode;
public:
	// Constructor & Destructor
	cDMLObjectNode();
	cDMLObjectNode(cDMLObject& object);
	~cDMLObjectNode() {};

	// Accessor
	cTreeNode<cDMLObject>* GetChild(std::string tag,
		std::string parameter, std::string parameter_value,
		std::string value) const;

	inline const std::vector<cDMLObjectNode*>& GetChildren()
	{
		return m_Children;
	}

	// Inquirer
	bool HasChild(const cDMLObjectNode* child) const;

	// Note : Check for replication!
	void AddChild(cDMLObjectNode* child);

	// Walk
	void Walk();
};

#endif