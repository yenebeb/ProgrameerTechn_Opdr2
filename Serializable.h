#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

// interface class
class Serializable {
	public:
	virtual void serialize(std::ostream &output) {}; // schrijft naar file
	virtual void deserialize(std::istream &input) {}; // leest van file
};

#endif