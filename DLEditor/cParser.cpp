#include "cParser.h"

cParser::cParser()	{
	m_TextSize = 0;
}

cParser::~cParser()	{
}

void cParser::AddRoot(std::string text, std::string value) {
	cNode* temp;
	temp = 0;
	temp->m_Text = text;
	temp->m_Value = value;
	m_Tree.push_back(temp);
}

void cParser::AddLeaf(std::string text, std::string value, cNode* root) {
	cNode* temp;
	temp = 0;
	temp->m_Text = text;
	temp->m_Value = value;
	root->m_Child.push_back(temp);
}

cNode* cParser::FindRoot(std::string text) {
	std::vector<cNode*>::iterator it;
	for (it = m_Tree.begin(); it != m_Tree.end(); it++) {
		if ((*it)->m_Text == text)
			return (*it);
	}
	return 0;
}

bool cParser::Validate(std::string text)	{
	/*if (text.size() < 1) return false;
	std::string temp1;
	temp1 = text;
	std::transform(temp1.begin(), temp1.end(), temp1.begin(), ::toupper);

	if (m_Validate.size() < 1) return false;
	std::vector<std::string>::iterator it;
	for (it=m_Validate.begin(); it!=m_Validate.end(); it++)	{
		std::string temp2;
		temp2 = (*it);
		std::transform(temp2.begin(), temp2.end(), temp2.begin(), ::toupper);
		if (temp1 == temp2)	return true;
	}
	return false;*/
	return true;
}

std::string cParser::GetTag(std::string text)	{
	// Must in the form of <a>blah</a>
	std::string temp, tag;
	int left, right;
	temp = text;
	//if (temp.length() < 3) return NULL;
	if (temp.at(0) != '<' || temp.at(text.length()-1) != '>') return NULL;
	// Extract two tags
	tag = ExtractTag(temp);
	if (tag!="N/A")	{
		if (Validate(tag))
			return tag;
	}
	return NULL;
}

std::string cParser::GetContent(std::string text)	{
	//Substring from first > to second < and then remove possible blanks
	std::string temp;
	int right1, left2;
	temp = text;
	//if (temp.length() < 3) return NULL;
	if (temp.at(0) != '<' || temp.at(text.length()-1) != '>') return NULL;
	right1 = GetTagRightLocation(temp);
	left2 = GetTagLeftLocation(temp.substr(right1+1)); 
	if (left2 > 0) return temp.substr(right1+1, left2);
}

int cParser::GetTagLeftLocation(std::string text)	{
	//if (text.length() < 7) return -1;
	for (int i=0; i < text.length(); i++)	{
		if (text.at(i) == '<') {
			return i;
			break;
		}
	}
	return -1;
}

int cParser::GetTagRightLocation(std::string text)	{
	//if (text.length() < 3) return -1;
	for (int i=0; i < text.length(); i++)	{
		if (text.at(i) == '>') {
			return i;
			break;
		}
	}
	return -1;
}

int cParser::GetTagEndLocation(std::string text)	{
	//if (text.length() < 3) return -1;
	for (int i=0; i < text.length(); i++)	{
		if (text.at(i) == '/') {
			return i;
			break;
		}
	}
	return -1;
}

std::string cParser::ExtractTag(std::string text)	{
	std::string temp;
	temp = text;
	int begin, end;
	begin = GetTagLeftLocation(temp);
	end = GetTagRightLocation(temp);

	if (begin <0 || end <0 || begin >= end) return "N\A";
	if (temp.substr(begin, end-begin).at(0) == '/')
		return temp.substr(begin+1, end-begin-1);
	else
		return temp.substr(begin+1, end-begin-1);
}

int cParser::ExtractTagValue(std::string lefttag) {
	//Note that lefttag must be extracted and passed to this function
	//Find '=' and extract whatever value after that and return
	std::string temp;
	for (int i = 0; i < lefttag.length(); i++) {
		if (lefttag.at(i) == '=') {
			temp = lefttag.substr(i + 1);
			break;
		}
	}
	if (temp.length() > 0)	return atoi(temp.c_str());
	else
	{
		return -1;
	}
}