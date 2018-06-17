#ifndef  __MYVALUE_H__
#define __MYVALUE_H__

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <iostream>

class MyValue;
typedef std::vector<MyValue> ValueVector;
typedef std::unordered_map<std::string, MyValue> ValueMap;
typedef std::unordered_map<int, MyValue> ValueMapIntKey;

class MyValue
{
public:
	/** A predefined Value that has not value. */
	static const MyValue Null;

	/** Default constructor. */
	MyValue();

	/** Create a Value by an unsigned char value. */
	explicit MyValue(unsigned char v);

	/** Create a Value by an integer value. */
	explicit MyValue(int v);

	/** Create a Value by an unsigned value. */
	explicit MyValue(unsigned int v);

	/** Create a Value by a float value. */
	explicit MyValue(float v);

	/** Create a Value by a double value. */
	explicit MyValue(double v);

	/** Create a Value by a bool value. */
	explicit MyValue(bool v);

	/** Create a Value by a char pointer. It will copy the chars internally. */
	explicit MyValue(const char* v);

	/** Create a Value by a string. */
	explicit MyValue(const std::string& v);

	/** Create a Value by a ValueVector object. */
	explicit MyValue(const ValueVector& v);
	/** Create a Value by a ValueVector object. It will use std::move internally. */
	explicit MyValue(ValueVector&& v);

	/** Create a Value by a ValueMap object. */
	explicit MyValue(const ValueMap& v);
	/** Create a Value by a ValueMap object. It will use std::move internally. */
	explicit MyValue(ValueMap&& v);

	/** Create a Value by a ValueMapIntKey object. */
	explicit MyValue(const ValueMapIntKey& v);
	/** Create a Value by a ValueMapIntKey object. It will use std::move internally. */
	explicit MyValue(ValueMapIntKey&& v);

	/** Create a Value by another Value object. */
	MyValue(const MyValue& other);
	/** Create a Value by a Value object. It will use std::move internally. */
	MyValue(MyValue&& other);

	/** Destructor. */
	~MyValue();

	/** Assignment operator, assign from Value to Value. */
	MyValue& operator= (const MyValue& other);
	/** Assignment operator, assign from Value to Value. It will use std::move internally. */
	MyValue& operator= (MyValue&& other);

	/** Assignment operator, assign from unsigned char to Value. */
	MyValue& operator= (unsigned char v);
	/** Assignment operator, assign from integer to Value. */
	MyValue& operator= (int v);
	/** Assignment operator, assign from integer to Value. */
	MyValue& operator= (unsigned int v);
	/** Assignment operator, assign from float to Value. */
	MyValue& operator= (float v);
	/** Assignment operator, assign from double to Value. */
	MyValue& operator= (double v);
	/** Assignment operator, assign from bool to Value. */
	MyValue& operator= (bool v);
	/** Assignment operator, assign from char* to Value. */
	MyValue& operator= (const char* v);
	/** Assignment operator, assign from string to Value. */
	MyValue& operator= (const std::string& v);

	/** Assignment operator, assign from ValueVector to Value. */
	MyValue& operator= (const ValueVector& v);
	/** Assignment operator, assign from ValueVector to Value. */
	MyValue& operator= (ValueVector&& v);

	/** Assignment operator, assign from ValueMap to Value. */
	MyValue& operator= (const ValueMap& v);
	/** Assignment operator, assign from ValueMap to Value. It will use std::move internally. */
	MyValue& operator= (ValueMap&& v);

	/** Assignment operator, assign from ValueMapIntKey to Value. */
	MyValue& operator= (const ValueMapIntKey& v);
	/** Assignment operator, assign from ValueMapIntKey to Value. It will use std::move internally. */
	MyValue& operator= (ValueMapIntKey&& v);

	/** != operator overloading */
	bool operator!= (const MyValue& v);
	/** != operator overloading */
	bool operator!= (const MyValue& v) const;
	/** == operator overloading */
	bool operator== (const MyValue& v);
	/** == operator overloading */
	bool operator== (const MyValue& v) const;

	/** Gets as a byte value. Will convert to unsigned char if possible, or will trigger assert error. */
	//unsigned char asByte() const;
	/** Gets as an integer value. Will convert to integer if possible, or will trigger assert error. */
	int asInt() const;
	/** Gets as an unsigned value. Will convert to unsigned if possible, or will trigger assert error. */
	unsigned int asUnsignedInt() const;
	/** Gets as a float value. Will convert to float if possible, or will trigger assert error. */
	float asFloat() const;
	/** Gets as a double value. Will convert to double if possible, or will trigger assert error. */
	double asDouble() const;
	/** Gets as a bool value. Will convert to bool if possible, or will trigger assert error. */
	bool asBool() const;
	/** Gets as a string value. Will convert to string if possible, or will trigger assert error. */
	std::string asString() const;

	/** Gets as a ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error. */
	ValueVector& asValueVector();
	/** Gets as a const ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error. */
	const ValueVector& asValueVector() const;

	/** Gets as a ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error. */
	ValueMap& asValueMap();
	/** Gets as a const ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error. */
	const ValueMap& asValueMap() const;

	/** Gets as a ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error. */
	ValueMapIntKey& asIntKeyMap();
	/** Gets as a const ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error. */
	const ValueMapIntKey& asIntKeyMap() const;

	/**
	* Checks if the Value is null.
	* @return True if the Value is null, false if not.
	*/
	bool isNull() const { return _type == Type::NONE; }

	/** Value type wrapped by Value. */
	enum class Type
	{
		/// no value is wrapped, an empty Value
		NONE = 0,
		/// wrap byte
		BYTE,
		/// wrap integer
		INTEGER,
		/// wrap unsigned
		UNSIGNED,
		/// wrap float
		FLOAT,
		/// wrap double
		DOUBLE,
		/// wrap bool
		BOOLEAN,
		/// wrap string
		STRING,
		/// wrap vector
		VECTOR,
		/// wrap ValueMap
		MAP,
		/// wrap ValueMapIntKey
		INT_KEY_MAP
	};

	/** Gets the value type. */
	Type getType() const { return _type; }

private:

	union
	{
		unsigned char byteVal;
		int intVal;
		unsigned int unsignedVal;
		float floatVal;
		double doubleVal;
		bool boolVal;

		std::string* strVal;
		ValueVector* vectorVal;
		ValueMap* mapVal;
		ValueMapIntKey* intKeyMapVal;
	}_field;

	Type _type;
};
#endif // ! __VALUE_H__
