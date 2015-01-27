DUV=cam
TEST=cam_test
OTHER_FILES=eff priorityencoder search_comb
BENCH=test
EFF_MODULE=eff_test
EFF=eff

.PHONY: test test-eff run run-eff view view-eff clean all leda

all: clean test run view
all-eff: clean test-eff run-eff view

test:
	vcs -full64 -PP -sverilog +define+SV +cli -line +define+VPD $(DUV).sv $(TEST).sv $(OTHER_FILES:=.sv) -o $(BENCH)

test-eff:
	vcs -full64 -PP -sverilog +define+SV +cli -line +define+VPD $(EFF).sv $(EFF_MODULE).sv -o $(EFF_MODULE)

run:
	./$(BENCH)

run-eff:
	./$(EFF_MODULE)

view:
	vpd2vcd vcdplus.vpd vcdplus.vcd &
	gtkwave vcdplus.vcd &

leda:
	leda -full64 -sverilog -top $(DUV) $(DUV).sv

clean:
	rm -rf csrc *.exe.daidir *.exe *.log *.inf .leda_work *.key *.vpd *.vcd DVEfiles $(BENCH) $(EFF_MODULE) *.daidir *~ test.vdb
