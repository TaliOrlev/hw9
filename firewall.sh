#!/bin/bash
chmod +x ./firewall.sh

while read rules; do

	rules=`echo "$rules" | tr -d ' ' | tr [A-Z] [a-z] | sed -e 's/#.*//'`

	#if the rule is empty, don't do anything
	if [[ "$rules" == "" ]]; then
		continue
	fi

	packets_found=""
	

	sub_rule=($(echo $rules | tr "," "\n"))
	for i in "${sub_rule[@]}"; do
		packets_found+=`./firewall.exe "$i" < $1`
		packets_found+="\n"

	done

	packets_final+=`echo -e "${packets_found}" | sed '/^$/d' | sort |\
	uniq -c  | grep -E "^ *${#sub_rule[@]} " | sed -e "s/^ *${#sub_rule[@]} //"`
	packets_final+="\n"

 done

echo -e "${packets_final}" | sed '/^$/d' | tr -d ' ' | sort