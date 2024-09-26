CXX = g++
CXXFLAGS = -std=c++11 -fopenmp `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`
TARGET = detector_rostros

SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) $(IMAGE)