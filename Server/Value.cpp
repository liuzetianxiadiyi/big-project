#include "Value.h"
class MyValue;
#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
MyValue::MyValue()
	: _type(Type::NONE)
{
	memset(&_field, 0, sizeof(_field));
}

MyValue::MyValue(unsigned char v)
	: _type(Type::BYTE)
{
	_field.byteVal = v;
}

MyValue::MyValue(int v)
	: _type(Type::INTEGER)
{
	_field.intVal = v;
}

MyValue::MyValue(unsigned int v)
	: _type(Type::UNSIGNED)
{
	_field.unsignedVal = v;
}

MyValue::MyValue(float v)
	: _type(Type::FLOAT)
{
	_field.floatVal = v;
}

MyValue::MyValue(double v)
	: _type(Type::DOUBLE)
{
	_field.doubleVal = v;
}

MyValue::MyValue(bool v)
	: _type(Type::BOOLEAN)
{
	_field.boolVal = v;
}

MyValue::MyValue(const char* v)
	: _type(Type::STRING)
{
	_field.strVal = new (std::nothrow) std::string();
	if (v)
	{
		*_field.strVal = v;
	}
}

MyValue::MyValue(const std::string& v)
	: _type(Type::STRING)
{
	_field.strVal = new (std::nothrow) std::string();
	*_field.strVal = v;
}

MyValue::MyValue(const ValueVector& v)
	: _type(Type::VECTOR)
{
	_field.vectorVal = new (std::nothrow) ValueVector();
	*_field.vectorVal = v;
}

MyValue::MyValue(ValueVector&& v)
	: _type(Type::VECTOR)
{
	_field.vectorVal = new (std::nothrow) ValueVector();
	*_field.vectorVal = std::move(v);
}

MyValue::MyValue(const ValueMap& v)
	: _type(Type::MAP)
{
	_field.mapVal = new (std::nothrow) ValueMap();
	*_field.mapVal = v;
}

MyValue::MyValue(ValueMap&& v)
	: _type(Type::MAP)
{
	_field.mapVal = new (std::nothrow) ValueMap();
	*_field.mapVal = std::move(v);
}

MyValue::MyValue(const ValueMapIntKey& v)
	: _type(Type::INT_KEY_MAP)
{
	_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
	*_field.intKeyMapVal = v;
}

MyValue::MyValue(ValueMapIntKey&& v)
	: _type(Type::INT_KEY_MAP)
{
	_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
	*_field.intKeyMapVal = std::move(v);
}

MyValue::MyValue(const MyValue& other)
	: _type(Type::NONE)
{
	*this = other;
}

MyValue::MyValue(MyValue&& other)
	: _type(Type::NONE)
{
	*this = std::move(other);
}

MyValue::~MyValue(){}

MyValue& MyValue::operator= (const MyValue& other)
{
	if (this != &other) {
		reset(other._type);

		switch (other._type) {
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::UNSIGNED:
			_field.unsignedVal = other._field.unsignedVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			if (_field.strVal == nullptr)
			{
				_field.strVal = new std::string();
			}
			*_field.strVal = *other._field.strVal;
			break;
		case Type::VECTOR:
			if (_field.vectorVal == nullptr)
			{
				_field.vectorVal = new (std::nothrow) ValueVector();
			}
			*_field.vectorVal = *other._field.vectorVal;
			break;
		case Type::MAP:
			if (_field.mapVal == nullptr)
			{
				_field.mapVal = new (std::nothrow) ValueMap();
			}
			*_field.mapVal = *other._field.mapVal;
			break;
		case Type::INT_KEY_MAP:
			if (_field.intKeyMapVal == nullptr)
			{
				_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
			}
			*_field.intKeyMapVal = *other._field.intKeyMapVal;
			break;
		default:
			break;
		}
	}
	return *this;
}

MyValue& MyValue::operator= (MyValue&& other)
{
	if (this != &other)
	{
		clear();
		switch (other._type)
		{
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::UNSIGNED:
			_field.unsignedVal = other._field.unsignedVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			_field.strVal = other._field.strVal;
			break;
		case Type::VECTOR:
			_field.vectorVal = other._field.vectorVal;
			break;
		case Type::MAP:
			_field.mapVal = other._field.mapVal;
			break;
		case Type::INT_KEY_MAP:
			_field.intKeyMapVal = other._field.intKeyMapVal;
			break;
		default:
			break;
		}
		_type = other._type;

		memset(&other._field, 0, sizeof(other._field));
		other._type = Type::NONE;
	}

	return *this;
}


MyValue& MyValue::operator= (unsigned char v)
{
	reset(Type::BYTE);
	_field.byteVal = v;
	return *this;
}

MyValue& MyValue::operator= (int v)
{
	reset(Type::INTEGER);
	_field.intVal = v;
	return *this;
}

MyValue& MyValue::operator= (unsigned int v)
{
	reset(Type::UNSIGNED);
	_field.unsignedVal = v;
	return *this;
}

MyValue& MyValue::operator= (float v)
{
	reset(Type::FLOAT);
	_field.floatVal = v;
	return *this;
}

MyValue& MyValue::operator= (double v)
{
	reset(Type::DOUBLE);
	_field.doubleVal = v;
	return *this;
}

MyValue& MyValue::operator= (bool v)
{
	reset(Type::BOOLEAN);
	_field.boolVal = v;
	return *this;
}

MyValue& MyValue::operator= (const char* v)
{
	reset(Type::STRING);
	*_field.strVal = v ? v : "";
	return *this;
}

MyValue& MyValue::operator= (const std::string& v)
{
	reset(Type::STRING);
	*_field.strVal = v;
	return *this;
}

MyValue& MyValue::operator= (const ValueVector& v)
{
	reset(Type::VECTOR);
	*_field.vectorVal = v;
	return *this;
}

MyValue& MyValue::operator= (ValueVector&& v)
{
	reset(Type::VECTOR);
	*_field.vectorVal = std::move(v);
	return *this;
}

MyValue& MyValue::operator= (const ValueMap& v)
{
	reset(Type::MAP);
	*_field.mapVal = v;
	return *this;
}

MyValue& MyValue::operator= (ValueMap&& v)
{
	reset(Type::MAP);
	*_field.mapVal = std::move(v);
	return *this;
}

MyValue& MyValue::operator= (const ValueMapIntKey& v)
{
	reset(Type::INT_KEY_MAP);
	*_field.intKeyMapVal = v;
	return *this;
}

MyValue& MyValue::operator= (ValueMapIntKey&& v)
{
	reset(Type::INT_KEY_MAP);
	*_field.intKeyMapVal = std::move(v);
	return *this;
}

bool MyValue::operator!= (const MyValue& v)
{
	return !(*this == v);
}
bool MyValue::operator!= (const MyValue& v) const
{
	return !(*this == v);
}

bool MyValue::operator== (const MyValue& v)
{
	const auto &t = *this;
	return t == v;
}
bool MyValue::operator== (const MyValue& v) const
{
	if (this == &v) return true;
	if (v._type != this->_type) return false;
	if (this->isNull()) return true;
	switch (_type)
	{
	case Type::BYTE:    return v._field.byteVal == this->_field.byteVal;
	case Type::INTEGER: return v._field.intVal == this->_field.intVal;
	case Type::UNSIGNED:return v._field.unsignedVal == this->_field.unsignedVal;
	case Type::BOOLEAN: return v._field.boolVal == this->_field.boolVal;
	case Type::STRING:  return *v._field.strVal == *this->_field.strVal;
	case Type::FLOAT:   return std::abs(v._field.floatVal - this->_field.floatVal) <= FLT_EPSILON;
	case Type::DOUBLE:  return std::abs(v._field.doubleVal - this->_field.doubleVal) <= DBL_EPSILON;
	case Type::VECTOR:
	{
		const auto &v1 = *(this->_field.vectorVal);
		const auto &v2 = *(v._field.vectorVal);
		const auto size = v1.size();
		if (size == v2.size())
		{
			for (size_t i = 0; i < size; i++)
			{
				if (v1[i] != v2[i]) return false;
			}
			return true;
		}
		return false;
	}
	case Type::MAP:
	{
		const auto &map1 = *(this->_field.mapVal);
		const auto &map2 = *(v._field.mapVal);
		for (const auto &kvp : map1)
		{
			auto it = map2.find(kvp.first);
			if (it == map2.end() || it->second != kvp.second)
			{
				return false;
			}
		}
		return true;
	}
	case Type::INT_KEY_MAP:
	{
		const auto &map1 = *(this->_field.intKeyMapVal);
		const auto &map2 = *(v._field.intKeyMapVal);
		for (const auto &kvp : map1)
		{
			auto it = map2.find(kvp.first);
			if (it == map2.end() || it->second != kvp.second)
			{
				return false;
			}
		}
		return true;
	}
	default:
		break;
	};

	return false;
}

/// Convert value to a specified type
/*unsigned char MyValue::asByte() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<unsigned char>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<unsigned char>(_field.unsignedVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<unsigned char>(atoi(_field.strVal->c_str()));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned char>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned char>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}*/

int MyValue::asInt() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::INTEGER)
	{
		return _field.intVal;
	}

	if (_type == Type::UNSIGNED)
	{
		//CCASSERT(_field.unsignedVal < INT_MAX, "Can only convert values < INT_MAX");
		return (int)_field.unsignedVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::STRING)
	{
		return atoi(_field.strVal->c_str());
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<int>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<int>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}


unsigned int MyValue::asUnsignedInt() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::UNSIGNED)
	{
		return _field.unsignedVal;
	}

	if (_type == Type::INTEGER)
	{
		//CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned");
		return static_cast<unsigned int>(_field.intVal);
	}

	if (_type == Type::BYTE)
	{
		return static_cast<unsigned int>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		// NOTE: strtoul is required (need to augment on unsupported platforms)
		return static_cast<unsigned int>(strtoul(_field.strVal->c_str(), nullptr, 10));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned int>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned int>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1u : 0u;
	}

	return 0u;
}

float MyValue::asFloat() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::FLOAT)
	{
		return _field.floatVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<float>(_field.byteVal);
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<float>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<float>(_field.unsignedVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<float>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0f : 0.0f;
	}

	return 0.0f;
}

double MyValue::asDouble() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<double>(_field.byteVal);
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<double>(_field.intVal);
	}

	if (_type == Type::UNSIGNED)
	{
		return static_cast<double>(_field.unsignedVal);
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<double>(_field.floatVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0 : 0.0;
	}

	return 0.0;
}

bool MyValue::asBool() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal == 0 ? false : true;
	}

	if (_type == Type::STRING)
	{
		return (*_field.strVal == "0" || *_field.strVal == "false") ? false : true;
	}

	if (_type == Type::INTEGER)
	{
		return _field.intVal == 0 ? false : true;
	}

	if (_type == Type::UNSIGNED)
	{
		return _field.unsignedVal == 0 ? false : true;
	}

	if (_type == Type::FLOAT)
	{
		return _field.floatVal == 0.0f ? false : true;
	}

	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal == 0.0 ? false : true;
	}

	return false;
}

std::string MyValue::asString() const
{
	//CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

	if (_type == Type::STRING)
	{
		return *_field.strVal;
	}
}

ValueVector& MyValue::asValueVector()
{
	//CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
	return *_field.vectorVal;
}

const ValueVector& MyValue::asValueVector() const
{
	//+CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
	return *_field.vectorVal;
}

ValueMap& MyValue::asValueMap()
{
	//CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
	return *_field.mapVal;
}

const ValueMap& MyValue::asValueMap() const
{
	//CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
	return *_field.mapVal;
}

ValueMapIntKey& MyValue::asIntKeyMap()
{
	//CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
	return *_field.intKeyMapVal;
}

const ValueMapIntKey& MyValue::asIntKeyMap() const
{
	//CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
	return *_field.intKeyMapVal;
}

void MyValue::reset(Type type)
{
	if (_type == type)
		return;
	
	clear();

	// Allocate memory for the new value
	switch (type)
	{
	case Type::STRING:
		_field.strVal = new (std::nothrow) std::string();
		break;
	case Type::VECTOR:
		_field.vectorVal = new (std::nothrow) ValueVector();
		break;
	case Type::MAP:
		_field.mapVal = new (std::nothrow) ValueMap();
		break;
	case Type::INT_KEY_MAP:
		_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
		break;
	default:
		break;
	}

	_type = type;
}

void MyValue::clear()
{
	// Free memory the old value allocated
	switch (_type)
	{
	case Type::BYTE:
		_field.byteVal = 0;
		break;
	case Type::INTEGER:
		_field.intVal = 0;
		break;
	case Type::UNSIGNED:
		_field.unsignedVal = 0u;
		break;
	case Type::FLOAT:
		_field.floatVal = 0.0f;
		break;
	case Type::DOUBLE:
		_field.doubleVal = 0.0;
		break;
	case Type::BOOLEAN:
		_field.boolVal = false;
		break;
	case Type::STRING:
		CC_SAFE_DELETE(_field.strVal);
		break;
	case Type::VECTOR:
		CC_SAFE_DELETE(_field.vectorVal);
		break;
	case Type::MAP:
		CC_SAFE_DELETE(_field.mapVal);
		break;
	case Type::INT_KEY_MAP:
		CC_SAFE_DELETE(_field.intKeyMapVal);
		break;
	default:
		break;
	}

	_type = Type::NONE;
}