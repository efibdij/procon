#!/bin/bash

if [ ! "$#" -eq 2 ]; then
	echo "error: wrong number of arguments"
	exit 1
fi

in_file="$1"
out_file="$2"

if [ ! -f "$in_file" ]; then
	echo "error: cannot find the input file"
	exit 1
fi

expanded=()

is_expanded() {
	local i
	for i in "${expanded[@]}"; do
		if [ "$i" = "$1" ]; then
			return 0
		fi
	done
	return 1
}

stl_included=()
code=()
prev_line=""

expand() {
	while IFS='' read -r line; do

		# Skip consecutive blank lines
		if [ -z "$line" ] && [ -z "$prev_line" ]; then
			continue
		fi

		# Take notes and skip STL
		if [[ $line =~ ^\ *#include\ *\<.+\>\ *$ ]]; then
			local stl=$(echo "$line" | grep -oP '#include\s*<\K[^>]+')
			stl_included+=("$stl")
			continue
		fi

		# Expand the header file
		if [[ $line =~ ^\ *#include\ *\".+\"\ *$ ]]; then

			local header=$(echo "$line" | grep -oP '#include\s*"\K[^"]+')

			if [ ! -f "$header" ]; then
				if [ ! -f "lib/$header" ]; then
					# Exit on error if the header file is not found
					echo "error: cannot find $header"
					exit 1
				fi
				header="lib/$header"
			fi

			if ! is_expanded "$header"; then
				expanded+=("$header")
				expand "$header"
			fi

		else

			# Skip include guards
			if [[ ! $line =~ ^\ *#.*LIB_.+_H_\ *$ ]]; then
				code+=("$line")
				prev_line="$line"
			fi

		fi

		# Add input/output optimization to the main function
		if echo "$line" | grep -q "main\s*(\s*)"; then
			code+=("	std::ios::sync_with_stdio(false);")
			code+=("	std::cin.tie(nullptr);")
		fi

	done < "$1"
}

expand "$in_file"

# Output to file

mkdir -p "$(dirname "$out_file")"
echo -n > "$out_file"

if [ ! "${#stl_included[@]}" -eq 0 ]; then
	stl_included=($(printf "%s\n" "${stl_included[@]}" | sort -u))
	printf "#include <%s>\n" "${stl_included[@]}" >> "$out_file"
	echo >> "$out_file"
fi

printf "%s\n" "${code[@]}" >> "$out_file"
