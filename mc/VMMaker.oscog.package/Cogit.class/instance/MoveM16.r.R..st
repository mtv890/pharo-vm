abstract instructions
MoveM16: offset r: baseReg R: destReg
	<inline: true>
	<returnTypeC: #'AbstractInstruction *'>
	^self gen: MoveM16rR operand: offset operand: baseReg operand: destReg