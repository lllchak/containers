CC = g++ -std=c++17
CFLAGS = -Wall -Wextra
TEST_DIR=tests
BUILD_DIR=build

SRC  := list/*.cpp
OBJS := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: clean s21_containers.a

test: clean
	$(CC) $(CFLAGS) $(SRC) -lgtest -o tests_res
	./tests_res
	rm tests_res

s21_containers.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_containers.a $(OBJS)
	ranlib s21_containers.a

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -f s21_containers.a
	rm -rf $(BUILD_DIR)
	rm -Rf *.o *.out

style-format:
	clang-format -i s21_containers.h $(SRC)

style-check:
	clang-format -n s21_containers.h $(SRC)

leaks: clean
	$(CC) $(CFLAGS) $(SRC) -lgtest -o tests_res

	valgrind --leak-check=full \
         	 --show-leak-kinds=all \
         	 --track-origins=yes \
         	 --verbose \
         	 ./tests_res

	rm tests_res

debug:
	$(CC) $(CFLAGS) test.cpp
	./a.out
	rm a.out

debug-leaks: clean
	$(CC) $(CFLAGS) test.cpp -lgtest -o tests_res

	valgrind --leak-check=full \
         	 --show-leak-kinds=all \
         	 --track-origins=yes \
         	 --verbose \
         	 ./tests_res

	rm tests_res
