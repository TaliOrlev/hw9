#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"


extern int check_args(int, char**);
extern void parse_input(Field&);

int main(int argc, char **argv) {

	if( check_args(argc, argv)==0 ) {
		return 1;
	}
	

	String rule(argv[1]);
	String *split_rule;
	size_t split_rule_size=0;
	rule.split("=", &split_rule, &split_rule_size);


	if (split_rule==NULL) {
		delete[] split_rule;
		return 0;
	}

	(split_rule[0])=(split_rule[0]).trim();
	(split_rule[1])=(split_rule[1]).trim();

	if ((split_rule[0]).equals("src-ip") || (split_rule[0]).equals("dst-ip")){
		Ip our_ip(split_rule[0]);
		our_ip.set_value(split_rule[1]);
		parse_input(our_ip);
	}

	if ((split_rule[0]).equals("src-port") ||
		(split_rule[0]).equals("dst-port")) {
		Port our_port(split_rule[0]);
		our_port.set_value(split_rule[1]);
		parse_input(our_port);
	}

	delete[] split_rule;

}