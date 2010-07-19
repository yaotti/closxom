all:	hello

hello:	hello.cc closxom_collector.cc closxom.cc
	g++ -o closxom.cgi -O2 hello.cc closxom_collector.cc closxom.cc

deploy_macosx:	hello.cgi
		cp ~/active/intern-prep/p/closxom/closxom.cgi /Library/WebServer/CGI-Executables

macosx: hello deploy_macosx