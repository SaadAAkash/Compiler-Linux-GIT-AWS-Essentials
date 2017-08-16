%%
(("http://"|"https://"|"ftp://")([a-zA-Z0-9\-\.])+([a-zA-Z0-9\-\.])*\.(com|COM|org|ORG|net|NET|edu|EDU)(":"[0-9]+))|(("http://"|"https://"|"ftp://")([a-zA-Z0-9\-\.])+([a-zA-Z0-9\-\.])*\.(com|COM|org|ORG|net|NET|edu|EDU)("/"[a-zA-Z0-9.#=_\-]+)*[a-zA-Z0-9.#=_\-]+)		{ printf("\n\nURL\n"); }
(("25"[0-5]|"2"[0-4][0-9]|([0-1]{0,1}))".")*("25"[0-5]|"2"[0-4][0-9]|([0-1]{0,1}))	{ printf("\n\nIP ADDRESS\n"); }
%%
