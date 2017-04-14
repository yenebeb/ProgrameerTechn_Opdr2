#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
class Serializable {
	public:
	virtual void serialize(std::ostream &output) {};
	virtual void deserialize(std::istream &input) {};
};

#endif