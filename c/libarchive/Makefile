O ?= build
TARGET = untar

.PHONY:all
all: $(TARGET) 

.PHONY: $(TARGET)
$(TARGET): $(O)
	@$(MAKE) -C $(O)

$(O):
	@mkdir $(O)
	@cd $(O) && cmake ..

.PHONY: clean
clean: 
	@rm -rf $(O) 
