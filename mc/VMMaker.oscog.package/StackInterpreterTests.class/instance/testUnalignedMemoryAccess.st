tests
testUnalignedMemoryAccess
	| om |
	om := NewCoObjectMemorySimulator new allocateMemoryOfSize: 16.
	om unalignedLongAt: 1 put: 16r11223344.
	self assert: (om unalignedLongAt: 0) equals: 16r22334400.
	self assert: (om unalignedLongAt: 4) equals: 16r11.
	self assert: (om unalignedLongAt: 1) equals: 16r11223344.
	om longAt: 0 put: 16rAAAAAAAA.
	om longAt: 4 put: 16rAAAAAAAA.
	om unalignedLongAt: 1 put: 16r11223344.
	self assert: (om unalignedLongAt: 0) equals: 16r223344AA.
	self assert: (om unalignedLongAt: 4) equals: 16rAAAAAA11.
	self assert: (om unalignedLongAt: 1) equals: 16r11223344.
	om := NewCoObjectMemorySimulator new allocateMemoryOfSize: 16.
	om unalignedLongAt: 3 put: 16r11223344.
	self assert: (om unalignedLongAt: 0) equals: 16r44000000.
	self assert: (om unalignedLongAt: 4) equals: 16r112233.
	self assert: (om unalignedLongAt: 3) equals: 16r11223344.
	om longAt: 0 put: 16rAAAAAAAA.
	om longAt: 4 put: 16rAAAAAAAA.
	om unalignedLongAt: 3 put: 16r11223344.
	self assert: (om unalignedLongAt: 0) equals: 16r44AAAAAA.
	self assert: (om unalignedLongAt: 4) equals: 16rAA112233.
	self assert: (om unalignedLongAt: 3) equals: 16r11223344.