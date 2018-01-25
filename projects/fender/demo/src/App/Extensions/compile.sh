g++ -fpic -shared "$1".cpp -W -Wall -Wextra -Werror -I../../../include -I../../../utils -I../../../../src -o "$1".so
