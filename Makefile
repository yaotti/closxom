all:	hello

hello:	hello.cc closxom_collector.cc closxom.cc
	g++ -o hello.cgi -O2 hello.cc closxom_collector.cc closxom.cc

deploy_mac:	hello.cgi
		cp ~/active/intern-prep/p/closxom/hello.cgi /Library/WebServer/CGI-Executables

macos: hello deploy_mac