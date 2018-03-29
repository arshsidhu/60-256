#!/bin/bash
a=`cat storage.txt`
a=$(($a + 8))

if((a>=100))
	then echo "from producer: Now I will take a rest!"
#adds 8 to the value in the file & executes consumer
else
	echo "from producer: current total is $a"
	echo $a > storage.txt
	./consumer
fi