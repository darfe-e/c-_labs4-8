# --- Переменные ---

# Компилятор C++
CXX = g++

# Флаги компилятора (C++20, все предупреждения)
CXXFLAGS = -std=c++20 -Wall -Wextra

# Флаги линкера (для библиотек, если нужны)
LDFLAGS = 

# Исполняемый файл
TARGET = 5_lab

# Директории для исходников
SRC_DIR_HEADERS = headers
SRC_DIR_SOURCE = source
SRC_DIR_EXCEPTIONS = exceptions
SRC_DIR_FILES_HEADERS = files/file_headers
SRC_DIR_FILES_SOURCE = files/file_source
# Для простоты, все файлы .cpp в корне и в source/ и files/file_source/
SRC_FILES = main.cpp \
	source/AlphabeticalCatalog.cpp \
	source/Article.cpp \
	source/ArticleCard.cpp \
	source/ArticleCollectionCard.cpp \
	source/BookCard.cpp \
	source/Catalog.cpp \
	source/IndependentPublicationCard.cpp \
	source/LibraryCard.cpp \
	source/ThematicCatalog.cpp \
	exceptions/func_with_exc.cpp \
	files/file_source/File_binary.cpp \
	files/file_source/File_text.cpp \
	library_manager.cpp

# --- Генерация списка объектных файлов ---
# Заменяем расширение .cpp на .o для всех исходных файлов
OBJS = $(SRC_FILES:.cpp=.o)


# --- Правила компиляции ---

# 1. Основное правило: Компиляция итогового исполняемого файла
$(TARGET): $(OBJS)
	@echo "--- Линковка $^ для создания $@ ---"
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 2. Общее правило для компиляции объектных файлов (.o из .cpp)
# < - имя зависимости (т.е. .cpp файл)
# $@ - имя цели (т.е. .o файл)
%.o: %.cpp
	@echo "Компиляция $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 3. Компиляция файлов в корне (main.cpp и library_manager.cpp)
main.o: main.cpp $(SRC_DIR_HEADERS)/*.h $(SRC_DIR_FILES_HEADERS)/*.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

library_manager.o: library_manager.cpp library_manager.h
	$(CXX) $(CXXFLAGS) -c library_manager.cpp -o library_manager.o

# 4. Общее правило для файлов в поддиректориях (source/, files/file_source/ и т.д.)
# Компиляция source/file.cpp в source/file.o
source/%.o: source/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

files/file_source/%.o: files/file_source/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

exceptions/%.o: exceptions/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# --- Утилиты ---

# Цель для очистки
.PHONY: clean
clean:
	@echo "Очистка объектных файлов и исполняемого файла..."
	rm -f $(TARGET) $(OBJS) source/*.o files/file_source/*.o exceptions/*.o