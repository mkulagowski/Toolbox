#pragma once
#include <limits>
#include <type_traits>
#include <utility>

template<size_t Size, typename ObjT, typename IdxT = unsigned int>
class StaticArray
{
	static_assert(Size > 0, "Size must be positive");
	static_assert(std::is_integral<IdxT>::value, "IdxT must be integer type");

public:
	class iterator {
	public:
		iterator(ObjT* ptr) : ptr(ptr) {}
		iterator operator++() { ++ptr; return *this; }
		bool operator!=(const iterator& other) const { return ptr != other.ptr; }
		ObjT& operator*() { return *ptr; }
	private:
		ObjT *ptr;
	};
	using const_iterator = const iterator;

	StaticArray() {};
	StaticArray(ObjT val) { fill(val); }

	iterator begin() { return iterator(data()); }
	iterator end() { return iterator(data() + Size); }
	const_iterator cbegin() const { return const_iterator(data()); }
	const_iterator cend() const { return const_iterator(data() + Size); }

	template<size_t OtherSize, typename OtherIdxT = IdxT>
	StaticArray(StaticArray<OtherSize, ObjT, OtherIdxT>& otherArray)
	{
		memcpy(mVals, otherArray.data(), sizeof(ObjT) * (Size <= OtherSize ? Size : OtherSize));
	}

	ObjT operator[](IdxT idx) const { return get(idx); }

	ObjT& operator[](IdxT idx) { return get(idx); }

	ObjT* data() { return &mVals[0]; }

	void fill(ObjT val)
	{
		for (auto &i : mVals)
			i = val;
	}

	void clear() { fill(static_cast<ObjT>(-1)); }
	
	void reverse()
	{
		for (int i = 0; i < Size / 2; ++i)
			std::swap(mVals[i], mVals[Size - 1 - i]);
	}

	StaticArray<Size, ObjT, IdxT> reverseCopy()
	{
		StaticArray<Size, ObjT, IdxT> resArr;
		for (int i = 0; i < Size / 2; ++i)
		{
			resArr[i] = mVals[Size - 1 - i];
			resArr[Size - 1 - i] = mVals[i];
		}
		return resArr;
	}

private:
	ObjT mVals[Size];

	template<typename Q = IdxT>
	typename std::enable_if<std::numeric_limits<Q>::is_signed, ObjT>::type & get(IdxT idx)
	{
		return mVals[idx < 0 ? Size + idx : idx];
	}

	template<typename Q = IdxT>
	typename std::enable_if<!std::numeric_limits<Q>::is_signed, ObjT>::type & get(IdxT idx)
	{
		return mVals[idx];
	}
};