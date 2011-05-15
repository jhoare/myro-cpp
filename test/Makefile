CC=g++
CFLAGS=`myro-cpp-config --cflags`
LIBS=`myro-cpp-config --libs`

BINARIES=test_blob test_camera test_motor video_stream test_camera_fourwindow test_camera_nonblocking

all: $(BINARIES) 

test_blob: test_blob.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

test_camera: test_camera.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

test_camera_fourwindow: test_camera_fourwindow.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

test_camera_nonblocking: test_camera_nonblocking.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

test_motor: test_motor.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

video_stream: video_stream.cpp
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f *.o core $(BINARIES)
