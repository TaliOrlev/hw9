#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "port.h"

#define ARRAY_LENGTH 2
#define MAX_PORT 65535

Port::Port(String pattern) :Field(pattern, PORT) {

} 

bool Port::set_value(String val) {

	String *split_port;
	size_t split_port_size=0;
	val.split("-", &split_port, &split_port_size);
	split_port[0]=split_port[0].trim();
	split_port[1]=split_port[1].trim();
	if (split_port==0 || (int)(split_port_size)!=(int)(ARRAY_LENGTH)) {
		delete[] split_port;
		return false;
	}
	range[0] = (split_port[0]).to_integer();
	range[1] = (split_port[1]).to_integer();


	/* check if port range is valid */
	if (range[0]<0 || range[0]>(int)(MAX_PORT) ||
		range[1]<0 || range[1]>(int)(MAX_PORT) ||
		range[0]>range[1]) {
		delete[] split_port;
		return false;
	}
	delete[] split_port;
	return true;
}

bool Port::match_value(String val) const {
	val=val.trim();
	int val_int=val.to_integer();
	return (val_int>=range[0] && val_int<=range[1]);
}