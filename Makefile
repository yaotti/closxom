CC = g++
CFLAGS = -g -Wall -O2
SRC = closxom.pb.cc closxom_storage_filesystem.cc closxom_storage_protobuf.cc closxom_collector.cc closxom.cc hello.cc
OBJ = closxom.pb.o closxom_storage_filesystem.o closxom_storage_protobuf.o closxom_collector.o closxom.o hello.o

.PHONY:	clean

all:	closxom proto

closxom:	$(OBJ)
	$(CC) $(CFLAGS) -o closxom.cgi $(OBJ) `pkg-config --cflags --libs protobuf`

closxom.pb.o:	closxom.pb.h closxom.pb.cc
	$(CC) $(CFLAGS) -c closxom.pb.cc

closxom_storage_filesystem.o:	closxom_storage.h closxom_storage_filesystem.h closxom_storage_filesystem.cc
	$(CC) $(CFLAGS) -c closxom_storage_filesystem.cc

closxom_storage_protobuf.o:	closxom_storage.h closxom_storage_protobuf.h closxom_storage_protobuf.cc
	$(CC) $(CFLAGS) -c closxom_storage_protobuf.cc

closxom_collector.o:	closxom_collector.h closxom_collector.cc
	$(CC) $(CFLAGS) -c closxom_collector.cc

closxom.o:	closxom.h closxom.cc
	$(CC) $(CFLAGS) -c closxom.cc

hello.o:	closxom.h hello.cc
	$(CC) $(CFLAGS) -c hello.cc

# for MacOS X
deploy_macosx:	closxom.cgi
		cp ./closxom.cgi /Library/WebServer/CGI-Executables
macosx: closxom deploy_macosx

# protocol buffer
proto: closxom.proto
	protoc --cpp_out=. closxom.proto

clean:
	rm $(OBJ)