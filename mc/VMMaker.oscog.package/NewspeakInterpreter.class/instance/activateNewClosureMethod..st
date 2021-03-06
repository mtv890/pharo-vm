control primitives
activateNewClosureMethod: blockClosure
	"Similar to activateNewMethod but for Closure and newMethod."
	| theBlockClosure closureMethod newContext methodHeader numCopied where outerContext |

	DoAssertionChecks ifTrue:
		[self okayOop: blockClosure].
	outerContext := self fetchPointer: ClosureOuterContextIndex ofObject: blockClosure.
	DoAssertionChecks ifTrue:
		[self okayOop: outerContext].
	closureMethod := self fetchPointer: MethodIndex ofObject: outerContext.
	methodHeader := self headerOf: closureMethod.
	self pushRemappableOop: blockClosure.
	newContext := self allocateOrRecycleContext: (methodHeader bitAnd: LargeContextBit). "All for one, and one for all!"

	"allocateOrRecycleContext: may cause a GC; restore blockClosure and refetch outerContext et al"
	theBlockClosure := self popRemappableOop.
	outerContext := self fetchPointer: ClosureOuterContextIndex ofObject: theBlockClosure.
	numCopied := (self fetchWordLengthOf: theBlockClosure) - ClosureFirstCopiedValueIndex.

	"Assume: newContext will be recorded as a root if necessary by the
	 call to newActiveContext: below, so we can use unchecked stores."
	where :=  newContext + BaseHeaderSize.
	self longAt: where + (SenderIndex << ShiftForWord)
		put: activeContext.
	self longAt: where + (InstructionPointerIndex << ShiftForWord)
		put: (self fetchPointer: ClosureStartPCIndex ofObject: theBlockClosure).
	self longAt: where + (StackPointerIndex << ShiftForWord)
		put: (self integerObjectOf: argumentCount + numCopied).
	self longAt: where + (MethodIndex << ShiftForWord)
		put: (self fetchPointer: MethodIndex ofObject: outerContext).
	self longAt: where + (ClosureIndex << ShiftForWord)
		put: theBlockClosure.
	self longAt: where + (ReceiverIndex << ShiftForWord)
		put: (self fetchPointer: ReceiverIndex ofObject: outerContext).

	"Copy the arguments..."
	1 to: argumentCount do:
		[:i | self longAt: where + ((ReceiverIndex+i) << ShiftForWord)
				put: (self stackValue: argumentCount-i)].

	"Copy the copied values..."
	where := newContext + BaseHeaderSize + ((ReceiverIndex + 1 + argumentCount) << ShiftForWord).
	0 to: numCopied - 1 do:
		[:i| self longAt: where + (i << ShiftForWord)
				put: (self fetchPointer: i + ClosureFirstCopiedValueIndex
						  ofObject: theBlockClosure)].

	"The initial instructions in the block nil-out remaining temps."

	self pop: argumentCount + 1.
	self newActiveContext: newContext