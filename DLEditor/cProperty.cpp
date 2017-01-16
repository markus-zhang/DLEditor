//#include "cProperty.h"
//#include <string>
//#include <tuple>
//
//struct Dog 
//{
//	std::string barkType;
//	std::string color;
//	int weight = 0;
//
//	bool operator==(const Dog& rhs) const {
//		return barkType == rhs.barkType && color == rhs.color && weight == rhs.weight;
//	}
//
//	constexpr static auto properties()
//	{
//		return std::make_tuple(
//			MakeProperty(&Dog::barkType, "barkType"),
//			MakeProperty(&Dog::color, "color"),
//			MakeProperty(&Dog::weight, "weight"));
//	}
//};
//
//struct cTestButton
//{
//	enum ButtonState
//	{
//		idle, hot, pressed
//	};
//	std::string m_ID;
//	// Image Clipping Information
//	int m_IdleImageX, m_IdleImageY;
//	int m_HotImageX, m_HotImageY;
//	int m_PressedImageX, m_PressedImageY;
//	// Button Position
//	int m_X, m_Y;
//	// Current State
//	ButtonState m_CurrentState;
//
//	/*bool operator==(const Dog& rhs) const {
//		return barkType == rhs.barkType && color == rhs.color && weight == rhs.weight;
//	}*/
//
//	constexpr static auto properties()
//	{
//		return std::make_tuple(
//			MakeProperty(&cTestButton::m_ID, "m_ID"),
//			MakeProperty(&cTestButton::m_IdleImageX, "m_IdleImageX"),
//			MakeProperty(&cTestButton::m_IdleImageY, "m_IdleImageY"),
//			MakeProperty(&cTestButton::m_HotImageX, "m_HotImageX"),
//			MakeProperty(&cTestButton::m_HotImageY, "m_HotImageY"),
//			MakeProperty(&cTestButton::m_PressedImageX, "m_PressedImageX"),
//			MakeProperty(&cTestButton::m_PressedImageY, "m_PressedImageY"));
//
//	}
//};