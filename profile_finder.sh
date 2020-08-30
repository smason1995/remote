# AWK shell script to find a specific profile form $XDGCONFIG/remote/profiles.txt

list=$1 # $XDGCONFIG/remote/profiles.txt
parm=$2 # Specific profle that we are looking for

# $result captures the output of AWK if the profile is found
result=$(awk -v item=$parm '{if($1 == item) print $2}' $list)

if [ -z "$result" ] # Checks if $result is empty
then
	echo "$parm not found" # Printed if $parm not found
else
	echo "$result" # Printed if $parm is found
fi
