#include <iostream>
#include <cstring>
#include "ip.h"
#include "string.h"

String::String () {
	this->data=NULL;
	this->length=0;	
}

String::String (const String &str) {
	if (str.length!=0) {
		this->length = str.length;
		this->data = new char [str.length+1];
		strncpy(this->data, str.data, str.length+1);
	} else {
		this->data=NULL;
		this->length=0;
	}
}

String::String (const char *str) {
	if (str==NULL) {
		this->data=NULL;
		this->length=0;
		return;
	} else {
		this->length = strlen(str);
		this->data = new char [strlen(str)+1];
		strncpy(this->data, str, this->length+1);
	}
}

String::~String () {
	if (this->data!=NULL) {
		delete[] data;
	}
}

String& String:: operator=(const String &rhs) {
	if (this->data!=NULL) {
		delete[] data;
	}

	int len=rhs.length;
	if (len==0) {
		this->data=NULL;
	} else {
		this->length=len;
		this->data = new char[len+1];
		strncpy(this->data, rhs.data, len+1);
	}
	
	return *this;
}

String& String:: operator=(const char *str) {
	if (str==NULL) {
		this->length=0;
		this->data=NULL;
		return *this;
	}

	if (this->data!=NULL) {
		delete[] data;
	}

	int len=strlen(str);
	if (len==0) {
		this->data=NULL;
	} else {
		this->length=len;
		this->data = new char[len+1];
		strncpy(this->data, str, len+1);
	}
	
	return *this;
}

bool String::equals(const String &rhs) const {
	if (rhs.data==NULL && this->data==NULL) {
		return true;
	}
	return (!strncmp(rhs.data, this->data, this->length));
}

   
bool String::equals(const char *rhs) const {
	if (rhs==NULL && this->data==NULL) {
		return true;
	}
	return (!strncmp(rhs, this->data, this->length));
}


void String::split(const char *delimiters, String **output, size_t *size) const{

	/* if delimiters are NULL, output=data */
	if (delimiters==NULL) {
		*size=1;
		*output= new String[1];
		String all_data_to_str;
		all_data_to_str= String(this->data);
		*output[0]=all_data_to_str;
		return;
	}
	if (output==NULL) {
		*size=0;
		return;
	}
	if (size==NULL) {
		*size=-1;
		return;
	}
	if (this->data==NULL) {
		*size=-1;
		return;
	}

	/* counting the number of sub-strings */
	int i=0, j=0, num_of_sub_str=1;
	while (i < (int)(this->length)) {
		while (j < (int)(strlen(delimiters))) {
			if (delimiters[j]==(this->data)[i]) {
				num_of_sub_str++;
				/* we break to handle duplicates in delimiters */
				break;
			}
			j++;
		}
		j=0;
		i++;
	}
	*size=num_of_sub_str;

	/* allocating the output */
	*output= new String[num_of_sub_str];

	i=0, j=0;
	int sub_str_index=0, start_sub=0;
	std::string data_str(this->data);
	std::string final_str;

	/* going over this and delimiters to find matches */
	while (i < (int)(this->length)) {
		while (j < (int)(strlen(delimiters))) {
			if (delimiters[j]==(this->data)[i]) {
				/* if the sub string is empty, break */
				if (i==start_sub) {
					start_sub=i+1;
					*size=(*size)-1;
					break;
				}
				/* converting to string, for substr */
				final_str=data_str.substr(start_sub, i-start_sub);

				/* converting to char, to copy and use c'tor of String */
				char *char_str= new char[final_str.length()+1];
				strcpy(char_str, final_str.c_str());

				/* placing the sub string to output */
				(*output)[sub_str_index]=String(char_str);
				start_sub=i+1;
				sub_str_index++;
				delete[] char_str;
			}
			j++;
		}
		j=0;
		i++;
	}

	/* last sub-string */
	if ((int)(this->length)==start_sub) {
		*size=(*size)-1;
	} else {
		final_str=data_str.substr(start_sub, (int)(this->length)-start_sub);
		char *char_str= new char[final_str.length()+1];
		strcpy(char_str, final_str.c_str());
		(*output)[sub_str_index]=String(char_str);
		delete[] char_str;
	}

}

int String::to_integer() const {
	return std::atoi(this->data);
}

String String::trim() const {
	int this_start_ind=0;
	int this_end_ind = (this->length)-1;

	/* finding the boundries of the string */
	while (this->data[this_start_ind]==' ') {
		this_start_ind++;
	}
	while ((this->data[this_end_ind]==' ')&&(this_start_ind!=this_end_ind)) {
		this_end_ind--;
	}
	this_end_ind++;

	if (this_start_ind>=this_end_ind) {
		return String();
	}

	/* placing the new string to output */
	std::string data_str(this->data);
	std::string final_str;
	final_str=data_str.substr(this_start_ind, this_end_ind-this_start_ind);
	char *char_str= new char[final_str.length()+1];
	strcpy(char_str, final_str.c_str());
	String no_spaces = String (char_str);
	return no_spaces;
}