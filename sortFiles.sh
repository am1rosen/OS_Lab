#!/bin/bash

catPath="/home/am1rosen/Desktop/Categorized"

# shellcheck disable=SC2164
cd $1

var=$(ls)
for filedir in $var;
do
	if [[ -f "$filedir" ]]; then
			mkdir -p "$catPath/${filedir##*.}Files"
			if [[ -f "$catPath/${filedir##*.}Files/$filedir" ]]; then
				filename=$(basename -- "$filedir")
				ext="${filename##*.}"
				new="${filename%.*}"
        	    		if [[ ! ${new: -1} == [0-9] ]]; then
        	    			new=$new"1"
        	    		fi
        	    		while true;
        	    		do
        	    			if [[ -f "$catPath/${filedir##*.}Files/$new.$ext" ]]; then
        	    				last=${new: -1}
        	    				if [[ $last -eq 9 ]]; then
        	    					if [[ ${new: -2: 1} == [1-9] ]]; then
        	    						if [[ ${new: -3: 1} == [1-9] ]]; then
        	    							last=${new: -3}
        	    							last=$((last+1))
        	    							new="${new::-3}$last"
        	    						else
        	    							last=${new: -2}
        	    							last=$((last+1))
        	    							new="${new::-2}$last"
        	    						fi
        	    					else
        	    						last=$((last+1))
        	    						new="${new::-1}$last"
        	    					fi
        	    				else
        	    					last=$((last+1))
        	    					new="${new::-1}$last"
        	    				fi
					else
						mv -n "$filedir" "$catPath/${filedir##*.}Files/$new.${filedir##*.}"
						break
        	    			fi
        	    		done
        	    	else
        	    		mv -n "$filedir" "$catPath/${filedir##*.}Files"
        	    	fi
	fi
done

