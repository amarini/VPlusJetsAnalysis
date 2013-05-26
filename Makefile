

.PHONY: BaseAnalysis
BaseAnalysis:
	cd BaseAnalysis && make

.PHONY: ZAnalysis
ZAnalysis: BaseAnalysis
	cd ZAnalysis && make

.PHONY: GAnalysis
GAnalysis: BaseAnalysis
	cd GAnalysis && make

.PHONY: QGDumper
QGDumper: BaseAnalysis
	cd QGDumper && make

.PHONY: zexe
zexe:
	cd ZAnalysis && make zexe
	[ -h zexe ] || ln -s ZAnalysis/zexe

.PHONY: TagAndProbe
TagAndProbe: BaseAnalysis
	cd TagAndProbe && make

.PHONY: tpexe
tpexe:
	cd TagAndProbe && make tpexe
	[ -h tpexe ] || ln -s TagAndProbe/tpexe
.PHONY: tpAnalysis
tpAnalysis:
	cd TagAndProbe && make tpAnalysis
	[ -h tpAnalysis ] || ln -s TagAndProbe/tpAnalysis

.PHONY: clean
clean:
	[ -h tpAnalysis ] && rm tpAnalysis || true
	[ -h tpexe ] && rm tpexe	 || true
	[ -h zexe ] && rm zexe || true
	cd BaseAnalysis && make clean || true
	cd ZAnalysis && make clean || true
	cd GAnalysis && make clean || true
	cd QGDumper && make clean || true
	cd TagAndProbe && make clean || true
