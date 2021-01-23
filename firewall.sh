#!/bin/bash
chmod +x ./firewall.sh

while read rules; do

	rules=`echo "$rules"|sed -e 's/#.*//'|tr -d ' '`

	if [[ "$rules" != "" ]]; then
		#split to sub-strings by ","
		sub_rule=($(echo $rules|tr "," "\n"))

		packets_found=""
		#for every sub-string of the rule, do firewall
		for i in "${sub_rule[@]}"; do
			packets_found+=`./firewall.exe "$i" < $1`
			packets_found+="\n"
		done

		#count only the packets that appeared N times, N=number of sub-rules
		packets_final+=`echo -e "${packets_found}"|sort|uniq -c|sed '/^$/d'|\
		grep -E "^ *${#sub_rule[@]} "|sed -e "s/^ *${#sub_rule[@]} //"`
		packets_final+="\n"
	fi

 done

echo -e "${packets_final}"|sort|sed '/^$/d'|tr -d ' '