#pragma once
#include <iostream>
#include <utility>
#include <initializer_list>
#include <unordered_map>
#include <optional>
#include <functional>

using namespace std;


template<class K, class T>
class MapList
{
private:
	unordered_map<K, T> mapList;

public:
	MapList() {}
	MapList(unordered_map<K, T> list) {
		this->mapList = list;
	}
	MapList(initializer_list<pair<K, T>> list) {
		this->put(list);
	}

	optional<T> findByKey(K key) {

		if (!this->contains(key))
			return {};

		return mapList.at(key);
	}

	optional<T> findBy(function<bool(K, T)> predicate) {
		for (auto& item : mapList) {
			if (predicate(item.first, item.second))
				return item.second;
		}
		return {};
	}

	T get(K key) {
		return mapList.find(key)->second;
	}

	bool contains(K key) {
		return mapList.find(key) != mapList.end();
	}

	MapList& put(K key, T value) {
		mapList[key] = value;
		return *this;
	}

	MapList& put(pair<K, T> keyValue) {
		return put(keyValue.first, keyValue.second);
	}
	
	void put(initializer_list<pair<K, T>> list) {
		for (auto& entry : list)
			put(entry.first, entry.second);
	}

	void put(MapList<K, T> list) {
		for (auto& entry : list.list())
			put(entry.first, entry.second);
	}


	unordered_map<K, T>& list() {
		return mapList;
	}
};

