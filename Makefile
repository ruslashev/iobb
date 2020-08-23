src = $(wildcard game/*.cc) \
      $(wildcard engine/*.cc) \
      $(wildcard engine/wm/glfw/*.cc)

cxx = g++
cflags = -g -std=c++17 -fno-exceptions -fno-rtti \
         -Wall -Wextra -Wpedantic -Wformat=2 -Wdouble-promotion -Wvla \
         -Wnull-dereference -Wredundant-decls -Wdisabled-optimization \
         -Wno-variadic-macros -Wno-unused-parameter -Wno-unused-variable -Wno-padded
lflags = $(shell pkg-config --libs glfw3 epoxy)
bin = iobb
builddir = build

objs = $(src:%.cc=$(builddir)/obj/%.o)
deps = $(src:%.cc=$(builddir)/dep/%.d)
obj2dep = $(@:$(builddir)/obj/%.o=$(builddir)/dep/%.d)
cflags += -MD -MP -MF $(obj2dep)

all: $(bin)
	./$(bin)

$(bin): $(objs)
	@echo "ld $(@F)"
	@$(cxx) $^ -o $@ $(lflags)

$(builddir)/obj/%.o: %.cc
	@echo "cxx $(<F)"
	@mkdir -p `dirname $@ $(obj2dep)`
	@$(cxx) $< -o $@ $(cflags) -c

clean:
	@echo "clean all"
	@rm -rf $(builddir) $(bin)

-include $(deps)
SHELL = bash

