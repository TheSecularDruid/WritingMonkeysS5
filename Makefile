main : 
	cc main.c --std=c99 -o output

clean :
	rm output

test_monkeyz :
	cc monkeyz.c -std=c99 -Werror -o test_monkeyz
	rm test_monkeyz
