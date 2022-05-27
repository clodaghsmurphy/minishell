RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

exec_pipe_test()
{
	rm diff3.txt
	echo $@ | ./minishell 2>&- > diff3.txt
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	TEST1=$(sed -i '$ d' diff3.txt && sed -i '1,1d' diff3.txt && cat diff3.txt )
	if [ "$TEST1" = "$TEST2" ] && [ "$ES_1" = "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	##else
	##	printf $BOLDGREEN"\nYour output : \n%.20s\n$BOLDGREEN$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
	sleep 0.1
}
printf " $BOLDWHITE PIPE TEST\n"
exec_pipe_test 'ls | cat'