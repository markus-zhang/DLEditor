#ifndef CPROPERTY_H_
#define CPROPERTY_H_

#include <map>
#include <string>

namespace DML
{
	struct cDMLData;
	struct cDML
	{
	public:
		std::map<std::string, cDMLData> m_Object;
		std::string m_StringValue;
		int m_IntValue;
	};

	struct cDMLData
	{
		cDML m_Data;

		cDMLData& operator[](std::string name)
		{
			return m_Data.m_Object[std::move(name)];
		}

		cDMLData& operator=(std::string value)
		{
			m_Data.m_StringValue = value;
			return *this;
		}

		cDMLData& operator=(int value)
		{
			m_Data.m_IntValue = value;
			return *this;
		}
	};

	template<typename T> T& AsAny(cDMLData&);
	template<>
	//template<typename T>
	inline int& AsAny<int>(cDMLData& data)
	{
		return data.m_Data.m_IntValue;
	}

	template<>
	inline std::string& AsAny<std::string>(cDMLData& data)
	{
		return data.m_Data.m_StringValue;
	}
}

template<typename Class, typename T>
class cProperty 
{
	cProperty(T Class::* member, const char* name) :
		member{ member }, name{ name } {}

	//using Type = T;

	T Class::*member;
	const char* name;


template<typename Class, typename T>
inline auto MakeProperty(T Class::*member, const char* name) {
	return cProperty<Class, T>{member, name};
}

template<std::size_t iteration, typename obj>
inline void DoSetData(obj&& object, /*const Json::Value& data*/ DML::cDMLData& data) 
{
	// get the property
	auto property = std::get<iteration>(std::decay_t<obj>::properties);

	// get the type of the property
	using Type = typename decltype(property)::Type;

	// set the value to the member
	object.*(property.member) = DML::AsAny<Type>data[property.name];
	//object.*(property.member) = Json::asAny<Type>(data[property.name]);
}

template<std::size_t iteration, typename T>
std::enable_if_t<(iteration > 0)>
inline SetData(T&& object, DML::cDMLData& data)
{
	DoSetData<iteration>(object, data);
	SetData<iteration - 1>(object, data);
}

template<std::size_t iteration, typename T>
std::enable_if_t<(iteration = 0)>
inline SetData(T&& object, DML::cDMLData& data)
{
	DoSetData<iteration>(object, data);
}

template<typename T>
inline T ReadDML(DML::cDMLData& data)
{
	T temp;
	SetData<std::tuple_size<decltype(std::decay_t<T>::properties)>::value - 1>(object, data);
	return temp;
}
};
#endif
