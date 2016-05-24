# Makefile

PROGRAM = a.out
SRCS = \
			main.cpp \
			GaussSeidel.cpp \
			DiffusionEq_CrankNicolson.cpp

# 定義済みマクロの再定義
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall
LIBS = -lgfortran -lblas -llapack -llapacke -lgsl -lgslcblas -fopenmp

# オブジェクトファイルは.cppを.oに置換したもの
OBJS = $(SRCS:.cpp=.o)

# 依存関係ファイル
DPNS = $(SRCS:.cpp=.d)

# プライマリターゲット
$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# パターンルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LIBS)

# .dファイルを読み込む
-include $(DPNS)

# .cppファイルを解析して、.cppが依存しているヘッダファイルを.dファイルに書き出す
%.d: %.cpp
	$(CXX) -M $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

run:
	./$(PROGRAM)

# make clean
clean:
	$(RM) $(PROGRAM) *.o *.d
