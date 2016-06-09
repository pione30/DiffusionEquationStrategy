# Makefile

# 定義済みマクロの再定義
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall
CPPFLAGS = -I ./include
LIBS = -lgfortran -lblas -llapack -llapacke -lgsl -lgslcblas -lfftw3 -fopenmp

SRCDIR = ./src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = ./obj
RESDIR = ./res
TARGETDIR = ./bin
PROGRAM = $(addprefix $(TARGETDIR)/, a.out)

# オブジェクトファイルは.cppを.oに置換したもの
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

# 依存関係ファイル
DPNS = $(OBJS:.o=.d)


# プライマリターゲット
$(PROGRAM): $(OBJS)
	@mkdir -p $(RESDIR)
	@mkdir -p $(TARGETDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# パターンルール
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $< $(LIBS)

# .dファイルを読み込む
-include $(DPNS)

# .cppファイルを解析して、.cppが依存しているヘッダファイルを.dファイルに書き出す
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -M $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

run:
	$(PROGRAM)

# make clean
clean:
	$(RM) $(PROGRAM) $(OBJS) $(DPNS) *.mp4
