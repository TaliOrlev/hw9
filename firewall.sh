#!/bin/bash
chmod +x ./firewall.sh

> results_packet.txt
> final_packets.txt
while read packet; do
	while read origin_rules; do
		clean_rule=`echo "$origin_rules"|sed -e 's/#.*//'|tr -d ' '`

		if [[ "$clean_rule" != "" ]]; then
		
			sub_rule=($(echo $clean_rule|tr "," "\n"))

			for i in "${sub_rule[@]}"; do
				echo "$packet" | ./firewall.exe "$i" >> results_packet.txt
			done

			num_of_apperences=`cat results_packet.txt | wc -l`

			if [[ num_of_apperences -eq ${#sub_rule[@]} ]]; then
				echo "$packet" >> final_packets.txt
			fi

			> num_of_apperences
			> results_packet.txt
		fi
	done < "$1"
done

cat final_packets.txt|sort|sed '/^$/d'|tr -d ' '

rm num_of_apperences
rm results_packet.txt
rm final_packets.txt