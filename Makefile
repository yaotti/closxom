all:	proto hello

hello:	hello.cc closxom.pb.cc closxom_storage.cc closxom_storage_filesystem.cc closxom_collector.cc closxom.cc
	g++ -o closxom.cgi -O2 hello.cc closxom.pb.cc closxom_storage.cc closxom_storage_filesystem.cc closxom_collector.cc closxom.cc `pkg-config --cflags --libs protobuf`

deploy_macosx:	closxom.cgi
		cp ./closxom.cgi /Library/WebServer/CGI-Executables

macosx: hello deploy_macosx

proto: closxom.proto
	protoc --cpp_out=. closxom.proto
