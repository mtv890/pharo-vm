I/O primitives
primitiveGetNextEvent
	"Primitive. Return the next input event from the VM event queue."
	| evtBuf arg value eventTypeIs |
	<var: #evtBuf declareC:'int evtBuf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }'>
	self cCode:'' inSmalltalk:[evtBuf := CArrayAccessor on: (IntegerArray new: 8)].
	arg := self stackTop.
	((objectMemory isArray: arg) and:[(objectMemory slotSizeOf: arg) = 8])  ifFalse:[^self primitiveFail].

	self ioGetNextEvent: (self cCoerce: evtBuf to: 'sqInputEvent*').
	self successful ifFalse:[^nil].

	"Event type"
	eventTypeIs := evtBuf at: 0.
	self storeInteger: 0 ofObject: arg withValue: (evtBuf at: 0).
	self successful ifFalse:[^nil].

	"Event is Complex, assume evtBuf is populated correctly and return"
	eventTypeIs = 6 
		ifTrue: [ 
			1 to: 7 do: [:i |
				value := evtBuf at: i.
				self storePointer: i ofObject: arg withValue: value]]
	ifFalse: [
		"Event time stamp"
		self storeInteger: 1 ofObject: arg withValue: ((evtBuf at: 1) bitAnd: MillisecondClockMask).
		self successful ifFalse:[^nil].	

		"Event arguments"
		2 to: 7 do:[:i|
			value := evtBuf at: i.
			(objectMemory isIntegerValue: value)
				ifTrue:[self storeInteger: i ofObject: arg withValue: value]
				ifFalse:[
					value := self positive32BitIntegerFor: value.
					objectMemory storePointer: i ofObject: arg withValue: value] ] ].

	self successful ifFalse:[^nil].
	self pop: 1