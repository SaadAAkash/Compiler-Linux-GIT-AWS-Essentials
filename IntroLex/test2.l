%{
	#include <stdio.h>
	#include "y.tab.h"
	int c;
%}
%%

"Hello" { printf("Hi!\n"); }

%% 



