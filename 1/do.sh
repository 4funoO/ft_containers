#!/bin/bash

make clean

mkdir ./logs

echo
echo INTRA_TEST:
c++ -Wall -Wextra -Werror -std=c++98 -D STD=1 ./test_intra.cpp -o std_containers
echo Time std:
time ./std_containers seed> ./logs/output_std
c++ -Wall -Wextra -Werror -std=c++98 ./test_intra.cpp -o ft_containers
echo
echo Time ft:
time ./ft_containers seed > ./logs/output_ft
diff ./logs/output_std ./logs/output_ft > ./logs/diff.diff
echo
echo Result:
if [ -s ./logs/diff.diff ]
	then
		echo "Possible Error. Check diff2.diff! (Diff in Leaks and Performance Report is OK.)"
	else
		echo OK
fi

echo
echo MY_TEST:
c++ -Wall -Wextra -Werror -std=c++98 -D STD=1 ./tests.cpp -o std_containers
echo Time std:
time ./std_containers seed > ./logs/output_std
c++ -Wall -Wextra -Werror -std=c++98 ./tests.cpp -o ft_containers
echo
echo Time ft:
time ./ft_containers seed > ./logs/output_ft
diff ./logs/output_std ./logs/output_ft > ./logs/diff.diff
echo
echo Result:
if [ -s ./logs/diff.diff ]
	then
		echo "Possible Error. Check diff2.diff! (Diff in Leaks and Performance Report is OK.)"
	else
		echo OK
fi