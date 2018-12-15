#pragma once
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <memory>
#include <algorithm>
class uHandlerCall_base
{
public:
	virtual void call(void*, void*)=0;
	virtual ~uHandlerCall_base() = default;
};
template<typename T1, typename T2>
class uHandlerCall : uHandlerCall_base
{
public:
	virtual void call(void* a, void* b) override
	{
		realCall(reinterpret_cast<T1*>(a), reinterpret_cast<T2*>(b));
	}
	std::function<void(T1*, T2*)> realCall;
	typedef std::function<void(T1*, T2*)> callType;
};
class uCollisionHandler
{

public:
	template<typename T>
	void registerGroup(uint32_t groupId)
	{
		typeMap.insert(groupId, std::type_index(typeid(T)));
	}
	template<typename T1,typename T2>
	void addCall(uint32_t groupId1, uint32_t groupId2, std::function<void(T1*,T2*)> fun)
	{
		/*static_assert(std::is_pointer<T1>::value, "Template type must not be a pointer!");
		static_assert(std::is_pointer<T2>::value, "Template type must not be a pointer!");
		assert(std::type_index(typeid(T1)) == typeMap.at(groupId1), "Type 1 does not match type assigned to Group 1");
		assert(std::type_index(typeid(T2)) == typeMap.at(groupId1), "Type 2 does not match type assigned to Group 2");*/

		auto index = std::minmax({ groupId1,groupId2 }); // to make unordered pair of groups (A,B) = (B,A)
		
		auto call = std::make_shared<uHandlerCall<T1, T2>>();
		call->realCall = fun;

		callMap.emplace(std::pair(index, call));
	}
	void call(uint32_t groupId1, uint32_t groupId2, void* arg1, void* arg2)
	{
		callMap.at(std::minmax({ groupId1,groupId2 }))->call(arg1, arg2);
	}
	bool contains(uint32_t gId1, uint32_t gId2)
	{
		if (callMap.count(std::minmax({ gId1,gId2 })) < 0) return true;
		else return false;
	}
private:
	std::unordered_map<uint32_t, std::type_index> typeMap;
	std::unordered_map<std::pair<uint32_t, uint32_t>, std::shared_ptr<uHandlerCall_base>> callMap;

};