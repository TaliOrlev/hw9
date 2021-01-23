#include <iostream>
#include <cstring>
#include "ip.h"
#include "field.h"

#define FIRST_IP_BITS 8
#define SECOND_IP_BITS 16
#define THIRD_IP_BITS 24
#define FOURTH_IP_BITS 32
#define MAX_IP 0xFFFFFFFF


Ip::Ip(String pattern) :Field(pattern, IP) {

}

bool Ip::set_value(String val) {
	String *split_mask;
	size_t split_mask_size=0;
	val.split("/", &split_mask, &split_mask_size);
	split_mask[0]=split_mask[0].trim();
	split_mask[1]=split_mask[1].trim();
	if (split_mask==NULL || (int)(split_mask_size)!=(int)(MASK_SEGMENT)) {
		delete[] split_mask;
		return false;
	}


	String *splited_ip;
	size_t splited_ip_size=0;

	int converted_mask_int = (split_mask[1]).to_integer();
	if (converted_mask_int<0||converted_mask_int>FOURTH_IP_BITS) {
		delete[] split_mask;
		return false;
	}

	if (converted_mask_int==0) {
		low=0;
		high=MAX_IP;
	}

	(split_mask[0]).split(".", &splited_ip, &splited_ip_size);

	if (splited_ip==0 || (int)(splited_ip_size)!=(int)(SEGMENTS)) {
		delete[] splited_ip;
		delete[] split_mask;
		return false;
	}


	int str_to_int=0, shift_factor=THIRD_IP_BITS;
	unsigned int tmp_ip=0, ip=0;
	for (int i=0; i<SEGMENTS; i++) {
		splited_ip[i]=splited_ip[i].trim();
		str_to_int=(splited_ip[i]).to_integer();
		tmp_ip=str_to_int<<shift_factor;
		shift_factor-=FIRST_IP_BITS;
		ip = ip | tmp_ip;
	}

	if (FOURTH_IP_BITS==converted_mask_int) {
		low=ip;
		high=ip;
		delete[] split_mask;
		delete[] splited_ip;
		return true;
	}

	ip = ip >> (FOURTH_IP_BITS-converted_mask_int);
	ip = ip << (FOURTH_IP_BITS-converted_mask_int);
	low = ip;

	high = (MAX_IP >> converted_mask_int);
	high = high|ip;

	delete[] split_mask;
	delete[] splited_ip;
	return true;

}


bool Ip::match_value(String val) const {
	String *splited_ip;
	size_t splited_ip_size=0;
	val.split(".", &splited_ip, &splited_ip_size);
	if (splited_ip==NULL || (int)(splited_ip_size)!=(int)(SEGMENTS)) {
		delete[] splited_ip;
		return false;
	}


	int str_to_int=0, shift_factor=THIRD_IP_BITS;
	unsigned int tmp_ip=0, ip=0;
	for (int i=0; i<SEGMENTS; i++) {
		splited_ip[i]=splited_ip[i].trim();
		str_to_int=(splited_ip[i]).to_integer();
		tmp_ip=str_to_int<<shift_factor;
		shift_factor-=FIRST_IP_BITS;
		ip+=tmp_ip;
	}

	delete[] splited_ip;
	return (ip>=low && ip<=high);
}


