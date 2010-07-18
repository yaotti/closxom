all:	hello.cc closxom_collector.cc closxom.cc
	g++ -o hello.cgi -O2 hello.cc closxom_collector.cc closxom.cc
	cp ~/active/intern-prep/p/closxom/hello.cgi /Library/WebServer/CGI-Executables
