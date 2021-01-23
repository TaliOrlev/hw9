#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "field.h"

#define SIZE_EMPTY_LINE -1

Field::Field(String pattern, field_type type) {
	this->pattern=pattern;
	this->type=type;
}

Field::Field(String pattern) {
	this->pattern=pattern;
	this->type=GENERIC;
}

Field::~Field() {

}

field_type Field::get_type() const {
	return this->type;
}

bool Field::set_value(String val) {
	if (get_type()==PORT) {
		return (((Port*)(this))->set_value(val));
	}
	if (get_type()==IP) {
		return (((Ip*)(this))->set_value(val));	
	}
	return false;
}

bool Field::match_value(String val) const {
	if (get_type()==PORT) {
		return (((Port*)(this))->match_value(val));
	}
	if (get_type()==IP) {
		return (((Ip*)(this))->match_value(val));	
	}
	return false;
}

bool Field::match(String packet) {

	String *first_output=NULL;
	size_t first_output_size=0;
	packet.split(",", &first_output, &first_output_size);

	/* if the line is empty, return false */
	if ((signed int)(first_output_size)==SIZE_EMPTY_LINE) {
		delete[] first_output;
		return false;
	}

	String *second_output=NULL;
	size_t second_output_size=0;

	/* for every sub-string in packet, split with "=" and search "this" */
	for (int i=0; i<(int)(first_output_size) ;i++) {
		(first_output[i]).split("=", &second_output, &second_output_size);
		if (second_output_size<=1) {
			delete[] second_output;
			second_output=NULL;
			continue;
		}
		second_output[0]=second_output[0].trim();
		second_output[1]=second_output[1].trim();
		if (pattern.equals(second_output[0])) {
			if (match_value(second_output[1])) {
				delete[] first_output;
				delete[] second_output;
				return true;
			}
		}
		delete[] second_output;
	}
	
	delete[] first_output;
	return false;
}
