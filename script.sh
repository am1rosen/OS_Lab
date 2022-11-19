#!/bin/bash


sort_files() {
	for i in *;
	do
		[ -f "$i" ] || continue								    # if $i is a file
			local filename=$(basename $i)						    # 'filename.ext'
			local ext="${filename##*.}"						    # 'ext'
			local current_dir=$(pwd)						    # /home/am1rosen/Desktop/Categorized/...
			mkdir -p ~/Desktop/Categorized/"$ext Files"				    # -p: no error if existing, make parents 

			if [ -f ~/Desktop/Categorized/"$ext Files"/"$filename" ] &&		    # if $i is already in catergorized dir 
			 [ "$current_dir" != "/home/am1rosen/Desktop/Categorized/""$ext Files" ];   # and if $i file is in another folder
			then									    # (if same file as $i is already in .ext files)
				rm $i								    # no need of $i; because already sorted
			else
				mv -n $i ~/Desktop/Categorized/"$ext Files"			    # -n: move without overwriting existing files
			fi
			
	done											    # sorting files of current folder is done
	manage_dirs										    # enter directories of current folder 
}

manage_dirs() {
	local dir_found=0
	for i in *;
	do
		[ -d "$i" ] || continue;
			dir_found=1								    # at least one directory found
			cd "$i"									    # if $i is a directory, enter it
			sort_files								    # sort files of the new directory
	done
	
	[ $dir_found -eq 0 ]									    # if folder is empty, go one directory back
		cd ..;
}


while true;
do
	cd ~/Desktop/Categorized
	sort_files
	cd ~/Desktop/Categorized
	find . -type d -empty -delete								    # find and delete empty directories recursively
	sleep 5
done

$SHELL												    # necessary for running 'cd' commands
