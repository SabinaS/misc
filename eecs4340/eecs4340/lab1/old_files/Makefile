DUV=cam
TEST=cam_test
OTHER_FILES=eff
BENCH=test


all: clean test run view

.PHONY: test
test:
	vcs -full64 -PP -sverilog +define+SV +cli -line +define+VPD $(DUV).sv $(TEST).sv $(OTHER_FILES:=.sv) -o $(BENCH)

.PHONY: run	
run:
	./$(BENCH)

.PHONY: view 	
view:
	vpd2vcd vcdplus.vpd vcdplus.vcd &
	gtkwave vcdplus.vcd &

.PHONY: leda
leda:
	leda -full64 -sverilog -top $(DUV) $(DUV).sv

.PHONY: clean	
clean:
	rm -rf csrc *.exe.daidir *.exe *.log *.inf .leda_work *.key *.vpd *.vcd DVEfiles $(BENCH) $(BENCH).daidir *~
