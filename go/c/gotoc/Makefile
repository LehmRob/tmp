all: gotoc

gotoc: libgotoc.a main.cpp
	$(CXX) -lpthread -o gotoc main.cpp ./libgotoc.a

libgotoc.a: gotoc.go
	go build -buildmode c-archive -o libgotoc.a gotoc.go

clean:
	rm -rf gotoc
	rm -rf libgotoc.a
	rm -rf libgotoc.h
