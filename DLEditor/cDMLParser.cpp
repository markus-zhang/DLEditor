#include "cDMLParser.h"

cDMLObjectNode::cDMLObjectNode() 
{
	m_RootPrt = NULL;
}

cDMLObjectNode::cDMLObjectNode(cDMLObject& object)
{
	m_RootPrt = new cTreeNode<cDMLObject>(object);
	m_CurrentDMLNode = m_RootPrt;
}

cTreeNode<cDMLObject>* cDMLObjectNode::GetChild(std::string tag,
	std::string parameter, std::string parameter_value,
	std::string value) const
{
	return m_RootPrt;
}

bool cDMLObjectNode::HasChild(const cDMLObjectNode* child) const
{
	return true;
}

void cDMLObjectNode::AddChild(cDMLObjectNode* child)
{
	// Check for replication
	assert(HasChild(child));

	// Push into children vector
	m_Children.push_back(child);
}

void cDMLObjectNode::Walk()
{
	std::cout << m_RootPrt->GetNodeContent().m_Tag <<
		" " << m_RootPrt->GetNodeContent().m_Parameter <<
		" " << m_RootPrt->GetNodeContent().m_ParameterValue <<
		" " << m_RootPrt->GetNodeContent().m_Value << "\n";

	std::vector<cDMLObjectNode*> :: const_iterator it;
	for (it = GetChildren().begin(); it != GetChildren().end(); it++)
	{
		(*it)->Walk();
	}
}