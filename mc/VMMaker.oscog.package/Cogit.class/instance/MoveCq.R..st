abstract instructions
MoveCq: quickConstant R: reg
	<inline: true>
	<returnTypeC: #'AbstractInstruction *'>
	^self gen: MoveCqR operand: quickConstant operand: reg