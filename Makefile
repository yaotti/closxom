all:	hello.cc closxom_collector.cc
	g++ -o hello.cgi -O2 hello.cc closxom_collector.cc
	cp ~/active/intern-prep/p/closxom/hello.cgi /Library/WebServer/CGI-Executables
